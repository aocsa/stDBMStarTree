#ifndef __stMStarTree_h__
#define __stMStarTree_h__

#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <deque>
#include <iostream>

#include "arboretum/stUtil.h"
#include "arboretum/stTypes.h"
#include "arboretum/stMetricTree.h"
#include "arboretum/stPageManager.h"
#include "arboretum/stGenericPriorityQueue.h"
#include "arboretum/stDBMCollection.h"
#include "arboretum/stDBMNode.h "

// A <- PageSize
// B <- ObjectSize
// C <- EntrySize
// D <- MStarNodeHeadSize


#define MSTAR_ORDER(A, B) ( floor(((A-NODE_HEAD_SIZE)/double(ENTRY_SIZE+B))) - 1)
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define STARTVALUEQUEUE 200
#define INCREMENTVALUEQUEUE 200

#include "MStarNode.h"
#include "stMStarLogicNode.h"
#include "stMStarMSTSplitter.h"

//=============================================================================
// Class template stMStarTree
//-----------------------------------------------------------------------------
/**
* @author Alexander Ocsa M. (alexocsa@unsa.edu.pe)
* @todo More documentation.??
* @todo Finish the implementation.??
* @version 1.0
*/
template<class ObjectType, class EvaluatorType>
class stMStarTree : public stMetricTree<ObjectType, EvaluatorType>{
public:
		
typedef struct stSubtreeInfo{
   ObjectType * Rep;
   stDistance	dOrepOnew;	
   stDistance	Radius;
   stPageID		RootID;
   stCount		NObjects;
   stCount		NEntries;
} tSubtreeInfo;

private:
struct stMStarHeader{
   int SplitMethod;
   int ChooseMethod;
   int idxRoot;
   stDistance TreeRadius;
   stPageID Root;
   /**
   * Minimum number of objects in a node.
   */
   stCount MaxOccupation;
   /**
   * Minimum percentage of objects in a node.
   */
   double	MinOccupation;
   stCount	ObjectCount;
   stSize	NodeCount;

   /**
   * If true, the reinsertion of object is done.
   */
   bool ReInsertObjects;
   /**
   * If true, remove farthest object to put new ones is perfomed.
   */
   bool RemoveFarthestObject;
   /**
   * The maximum number of promoted representatives.
   */
   stCount NumberOfClusters;
   /**
   * The height of the MSTAR-tree
   */
   stCount Height;

   stSize  Order;
};

public:

    /**
    * These constants are used to define the choose sub tree method.
    */
    enum tChooseMethod{
        MINGDIST,
        cmMINDIST,
		cmMINDISTWITHCOVER,
		/**
         * Density Based Hybrid ChooseSubTree.
         */
        cmDBHCS
    };

    enum tSplitMethod{
        smMIN_MAX,
		smN_SPLIT,
        MST_SLIM
    };

    /**
    * This is the class that abstracs an result set.
    */
    typedef stResult <ObjectType> tResult;
    typedef ObjectType            tObject;

    /**
    * This type is a memory node.
    */
    //typedef stMSTARMemNode < ObjectType > tMSTARMemNode;

    stMStarTree(stPageManager* pageman);
    virtual ~stMStarTree();
    virtual bool Add(tObject* obj);
    virtual stCount GetHeight(){
        return m_Header->Height;
    }

    /**
    * Returns the radius of the tree.
    */
	stDistance GetTreeRadius(){
		return m_Header->TreeRadius;
    }//end GetTreeRadius

      /**
      * Returns if the split method has already been called.
      */
      bool IsMinOccupationMapped(){
         return m_MinOccupationMapped;
      }//end IsMinOccupationMapped

      /**
      * Returns the MaxOccupation of the nodes.
      */
      stCount GetMaxOccupation(){
         return MSTAR_ORDER(PAGE_SIZE, OBJECT_SIZE);
      }//end GetMaxOccupation

      /**
      * Returns the MaxOccupation of the nodes.
      */
      void SetMaxOccupation(stCount newValue){
         if (newValue > m_Header->MaxOccupation){
            m_Header->MaxOccupation = newValue;
         }//end if
      }//end SetMaxOccupation

      /**
      * Returns the MinOccupation of the nodes.
      */
      virtual double GetMinOccupation(){
         return m_Header->MinOccupation;
      }//end GetMinOccupation

      /**
      * Sets the MinOccupation of the node.
      */
      virtual void SetMinOccupation(double MinOccup){
         m_Header->MinOccupation = MinOccup;
         // the occupation has already mapped.
         this->m_MinOccupationMapped = true;
         m_HeaderUpdate = true;
      }//end SetMinOccupation

    virtual long GetNodeCount(){
         return m_Header->NodeCount;
    }
	/**
	* Returns the number of objetcs of this tree.
	*
	* @return The number of objects indexed by the tree or -1 if this information is not available.
	*/
	long GetNumberOfObjects(){
		return m_Header->ObjectCount;
	}//end GetNumberOfObjects


    void SetSplitMethod(enum tSplitMethod method){
         m_Header->SplitMethod = method;
         m_HeaderUpdate = true;
    }
    int GetSplitMethod(){
         return m_Header->SplitMethod;
    }
    void SetChooseMethod(enum tChooseMethod method){
         m_Header->ChooseMethod = method;
         m_HeaderUpdate = true;
    }
    int GetChooseMethod(){
         return m_Header->ChooseMethod;
    }
    stCount GetNumberOfClusters(){
        return m_Header->NumberOfClusters;
    }
    bool IsRemoveFarthest(){
		return m_Header->RemoveFarthestObject;
	}//end IsRemoveFarthest

	bool IsReInsert(){
		return m_Header->ReInsertObjects;
	}//end IsReInsert

	void WriteHeader() {
		if(m_HeaderUpdate == true) {
			this->myPageManager->WriteHeaderPage(m_HeaderPage);
			m_HeaderUpdate = false;
		}
	}


    virtual tResult * RangeQuery(tObject * sample, stDistance range);

	virtual tResult * NearestQuery(tObject * sample, stCount k, bool tie = false);
    /*virtual tResult * PointQuery(tObject * sample);
    virtual bool Delete(tObject * obj);*/
    virtual void Optimize() {

	}

    void SetReInsert(bool flag) {
        m_Header->ReInsertObjects = flag;
        m_HeaderUpdate = true;
    }
    void SetRemoveFarthest(bool flag) {
        m_Header->RemoveFarthestObject = flag;
        m_HeaderUpdate = true;
    }
	void Show() {
		Show(GetRoot(), 0);
	}
	void Show(stPageID pageID, stCount level);

	bool CheckNode(stPageID pageID);
	bool CheckAllDistances() {
		//printf("first, %d \n", GetRoot());
		return CheckAllDistances( m_Header->TreeRadius, GetRoot());
	}
    double GetDistanceLimit(){
        if(CheckAllDistances()) {
            return 10.0;
        }
        else {
            return -1.0;
        }
    }
	bool CheckDistribution(stPageID pageID);
	bool CheckDistribution(stMStarNode* node);

	bool CheckAllDistances(stDistance radius, stPageID pageID);

private:
    void LoadHeader();
	void DefaultHeader();

    int InsertRecursive(stPageID currNodeID, tSubtreeInfo& newSubTree,
            ObjectType * repObj, tSubtreeInfo & farthest,
            tSubtreeInfo * promo);

    stPageID GetRoot(){
        return m_Header->Root;
    }
	void SetRoot(stPageID pageID){
		m_Header->Root = pageID;
	}
    void UpdateObjectCounter(int inc){
         m_Header->ObjectCount += inc;
         m_HeaderUpdate = true;
    }
	stDistance Infinite() {
		return MAXDOUBLE;
	}
	stSize GetOrder() {
		return m_Header->Order;
	}
	stPage* NewPage() {
		++m_Header->NodeCount;
		return this->myPageManager->GetNewPage();
	}
	bool RemoveFarthest(stMStarNode* currNode, tSubtreeInfo& newSubTree,tSubtreeInfo& farthest);
	void ReInsert(stMStarNode* node);

	int ChooseSubTree(stMStarNode* node, tSubtreeInfo& newSubTree);
	void AddNewRoot(tSubtreeInfo* promo);
	void Split(stMStarNode* node, tSubtreeInfo* promo);

	/**
	* Updates the distances of the objects from the new representative.
	*/
	void UpdateDistances(stMStarNode* node, ObjectType * repObj, int repObjIdx);

	/**
	* Updates the distances of the objects from the new representative.
	*/
	stCount ChooseRepresentative(stMStarNode* node);
	void	PrintNode(stMStarNode* node);
private:
	
	/**
	* This type defines the logic node for this class.
	*/
	typedef stMStarLogicNode < ObjectType, EvaluatorType > tLogicNode;

	/**
	* This type defines the MST splitter for this class.
	*/
	typedef stMStarSplitter < ObjectType, EvaluatorType > tMSTSplitter;

	/**
	* This type defines the MST splitter for this class.
	*/
//	typedef stMSTARNSplitter < ObjectType, EvaluatorType > tMSTARNSplitter;

	
	typedef stDBMMemNode < ObjectType > tDBMMemNode;


	typedef stDBMCollection<ObjectType> tDBMCollection;

    typedef stRPriorityQueue < stDistance, stCount > tPriorityQueue;
    typedef stDynamicRPriorityQueue < stDistance, stQueryPriorityQueueValue > tDynamicPriorityQueue;
    typedef stGenericPriorityHeap < ObjectType > tPGenericHeap;
    enum stInsertAction{
         /**
         * No action required. Just update the radius.
         */
         NO_ACT,

         /**
         * Replace representative.
         */
         CHANGE_REP,

         /**
         * Split occured. Update subtrees.
         */
         PROMOTION,

         /**
         * Farthest removed.
         */
         REMOVE_FARTHEST,

         /**
         * The node was removed.
         */
         REMOVED_NODE
      };//end stInsertAction
	enum stCloseness {
		DBHCS_HIGH,
		DBHCS_MIDDLE,
		DBHCS_VERY_LOW
	};
    /**
    * If true, the split method has already been called.
    */
    bool m_MinOccupationMapped;

    /**
    * If true, the m_Header mus be written to the page manager.
    */
    bool m_HeaderUpdate;

    /**
    * The MStarTree m_Header. This variable points to data in the HeaderPage.
    */
    stMStarHeader *		m_Header;
    stPage *			m_HeaderPage;
	tDBMCollection*		returnCollection;
	tDBMCollection*		reInsertCollection;
	/**
	* Updates all distances between representatives and all objects in this
	* node. It returns the number of distances calculated.
	*
	* @param metricEvaluator The metric evaluator to be used.
	*/
	stCount UpdateDistances(EvaluatorType * metricEvaluator);
	void	MinMaxRadiusPromoteSlim(tLogicNode * node) ;

	void	UpdateDCMatrix(stMStarNode* node, stCount idxReplacedObj);
	void	UpdateDCMatrix(stMStarNode* node);
	bool    CheckLemma1(stMStarNode* node,const stCount &i, int &k, stDistance &dOrepQ, stDistance & radius,  stDistance& dOkQ, ObjectType* query);
	void RangeQuery(stPageID currPageID, ObjectType* sample, stDistance &range, stDistance& dOrepOj, tResult *&queryResult);
    void NearestQuery(tResult * result,
         ObjectType * sample, stDistance rangeK, stCount k,
         tDynamicPriorityQueue * queue);

};

//////////////////////////////////////////////////////////////////////////

template<class ObjectType, class EvaluatorType>
stMStarTree<ObjectType, EvaluatorType>::stMStarTree(stPageManager* pageman)
	: stMetricTree<ObjectType, EvaluatorType>(pageman)
{
    m_Header = NULL;
    m_HeaderPage = NULL;
    LoadHeader();
    if(this->myPageManager->IsEmpty()) {
        DefaultHeader();
    }

	// Allocate the collections.
	this->returnCollection = new tDBMCollection();
	if(this->IsReInsert()) {
		this->reInsertCollection = new tDBMCollection();
	}
	else {
		this->reInsertCollection = NULL;
	}
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::LoadHeader()
{
	if(m_HeaderPage != NULL)
		this->myPageManager->ReleasePage(m_HeaderPage);
	m_HeaderPage = this->myPageManager->GetHeaderPage();
	if( m_HeaderPage->GetPageSize() <= sizeof(stMStarHeader))
		throw page_size_error("The page size id too small.");
	m_Header = (stMStarHeader *)m_HeaderPage->GetData();
	m_HeaderUpdate = false;
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::DefaultHeader()
{
    m_HeaderPage->Clear();
    m_Header->SplitMethod = smMIN_MAX;
    m_Header->ChooseMethod = stMStarTree::cmDBHCS;
    //m_Header->ChooseMethod =  cmMINDISTWITHCOVER;
    this->SetReInsert(false);
    this->SetRemoveFarthest(false);
    m_Header->Root = 0;
    m_Header->MinOccupation = 0.25;
    m_Header->Height = 0;
    m_Header->ObjectCount = 0;
    m_Header->TreeRadius = 0.0;
    m_Header->idxRoot = -1;
    m_Header->NumberOfClusters = 2;

   // Notify modifications
   m_HeaderUpdate = true;
}


template<class ObjectType, class EvaluatorType>
stMStarTree<ObjectType, EvaluatorType>::~stMStarTree()
{
	if(m_HeaderPage != NULL){
		if(m_Header != NULL)
			WriteHeader();
		this->myPageManager->ReleasePage(m_HeaderPage);
	}
	delete this->returnCollection;
	if( this->IsReInsert() ) {
		delete this->reInsertCollection;

	}
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::Add(tObject* obj)
{
	#ifdef __stDEBUB__
	printf("**enter, add, rootID = %d \n", GetRoot());
	cout << *obj << endl;		 
	#endif

	tSubtreeInfo * promo;
	tSubtreeInfo newSubTree;
	tSubtreeInfo farthest;

	stMStarNode* rootNode;
	stPage* rootPage;
	int insertIdx;
	int idxPromo, idxReturn;

	if(GetRoot() == 0) {
		m_Header->Order = MSTAR_ORDER(PAGE_SIZE, obj->GetSerializedSize()); // Set order of the tree
		//printf("order tree: %d\n", m_Header->Order);
		rootPage = this->NewPage();
		rootNode = new stMStarNode(rootPage, m_Header->Order);
		insertIdx = rootNode->AddEntry(obj->GetSerializedSize(), obj->Serialize(), 0);
		
		#ifdef __stDEBUB__
		if ( insertIdx < 0) {
			throw page_size_error("The page size is too small to store the first object");
		}
		#endif //__stDEBUB__
		rootNode->GetEntry(insertIdx).Distance = 0.0;
		rootNode->SetRadius(insertIdx, 0);
		rootNode->SetNEntries(insertIdx, 0);

		this->SetRoot(rootPage->GetPageID());
		
		m_Header->idxRoot = 0;
		m_Header->Height = 1; // Update Height
		m_Header->TreeRadius = 0.0;
		m_Header->idxRoot = 0;

		this->myPageManager->WritePage(rootPage);
		delete rootNode;
		this->myPageManager->ReleasePage(rootPage);
		#ifdef __stDEBUB__
		printf("first object\n");
		#endif
	}
	else {
		newSubTree.Rep		= obj;
		newSubTree.Radius   = 0.0;
		newSubTree.RootID   = 0;
		newSubTree.NObjects = 0;
		//newSubTree.Height   = 0;
		newSubTree.dOrepOnew  = 0.0;

		promo = new tSubtreeInfo[GetNumberOfClusters()];
		for (idxPromo = 0; idxPromo < GetNumberOfClusters(); idxPromo++){
			promo[idxPromo].Rep = NULL;
		}
		#ifdef __stDEBUB__
		printf("recursive insert\n");
		#endif

		if (this->InsertRecursive(this->GetRoot(), newSubTree, NULL, farthest, promo) == PROMOTION){
			#ifdef __stDEBUB__
			printf("add new root\n");
			#endif

			this->AddNewRoot(promo);
		}
		if( this->IsReInsert() ) {
			idxReturn = reInsertCollection->GetNumberOfEntries();
			// While there is object...
			while (idxReturn > 0) {
				newSubTree.Rep = (* reInsertCollection)[idxReturn-1]->GetObject();
				newSubTree.Radius = (* reInsertCollection)[idxReturn-1]->GetRadius();
				newSubTree.RootID = (* reInsertCollection)[idxReturn-1]->GetPageID();
//				newSubTree.NObjects= (* reInsertCollection)[idxReturn-1]->GetNEntries();

				(* reInsertCollection)[idxReturn-1]->SetMine(false);
				reInsertCollection->RemoveLast();
				
				#ifdef __stDEBUB__
				cout << "reinsert object\n";
				CheckNode(GetRoot());
				#endif
				if (InsertRecursive(this->GetRoot(), newSubTree, NULL, farthest, promo) == PROMOTION){
					// Split occurred! We must create a new root because it is required.
					// The tree will acquire a new root.
					AddNewRoot(promo);
				}//end if
				// Clean.
				delete newSubTree.Rep;
				// update the number of entries.
				idxReturn = reInsertCollection->GetNumberOfEntries();
			}//end while
		}//end if
		m_Header->TreeRadius = promo[0].Radius;
		delete[] promo;
	}
	
	#ifdef __stDEBUB__
	cout << "edn_add::root_node\n";
	CheckNode(GetRoot());
	#endif
	UpdateObjectCounter(1);
	m_HeaderUpdate = true;
	return true;
}

template<class ObjectType, class EvaluatorType>
int stMStarTree<ObjectType, EvaluatorType>::InsertRecursive(  stPageID currNodeID,
                                                              tSubtreeInfo& newSubTree,
                                                              ObjectType * repObj,
                                                              tSubtreeInfo & farthest,
                                                              tSubtreeInfo * promo)
{
	int result;
	int insertIdx;
	int subTree;
	stPage* currPage;
	stMStarNode* currNode;
	stCount idx;			
	
	currPage = this->myPageManager->GetPage( currNodeID );
	currNode = new stMStarNode(currPage);
	
	subTree = ChooseSubTree(currNode, newSubTree);
	
	if (subTree >= 0) {
		ObjectType* subRep = new ObjectType();
		subRep->Unserialize( currNode->GetObject(subTree), currNode->GetObjectSize(subTree));
	
		// Is this a SubTree?
		if ( currNode->IsSubTree(subTree) ) {
			//Yes, It is a SubTree Entry
			#ifdef __stDEBUB__
			printf("recursive insert\n");
			#endif
			//cout << "before, insertRecursive: subtree = " << subRep->GetStr() << "\n";
			switch( InsertRecursive( currNode->GetEntry(subTree).PageID, newSubTree, subRep, farthest, promo) ) {
			case NO_ACT:
				#ifdef __stDEBUB__
				printf("no act\n");
				#endif

				currNode->SetRadius(subTree, promo[0].Radius);
				currNode->SetNEntries(subTree, promo[0].NObjects);

				this->ReInsert(currNode);

				promo[0].Radius = currNode->GetMinimumRadius();
				promo[0].NObjects = currNode->GetTotalObjectCount();
				
				#ifdef __stDEBUB__
				CheckNode(currNodeID);
				#endif

				result = NO_ACT;
				break;
			
			case PROMOTION:
				#ifdef __stDEBUB__
				printf("promotion\n");
				cout << "  *****currSubTree: " << subTree << "\n";
				cout << "  -before promotion\n";
				CheckDistribution(currNode);
				#endif

				//stDistance distanceOjOidxRoot;
				idx = 1; 
				bool stop;
				
				currNode->SetEntry(	promo[0].Rep->Serialize(),
									promo[0].Rep->GetSerializedSize(),
									promo[0].RootID,
									subTree );

				currNode->GetEntry(subTree).Distance = -1.0;	//in this moment has invalid distance
				currNode->SetRadius(subTree, promo[0].Radius);
				currNode->SetNEntries(subTree, promo[0].NObjects);

				delete promo[0].Rep;
				promo[0].Rep = NULL;
				
				stop = (idx == GetNumberOfClusters());
				
				// Add the promo object to the current node.
				while (!stop) {
					if (promo[idx].Rep) {
						insertIdx = currNode->AddEntry( promo[idx].Rep->GetSerializedSize(),
														promo[idx].Rep->Serialize(),							
														promo[idx].RootID);
						///////// xQxQxQ?????????????????///////////////////////////////////////
						UpdateDCMatrix(currNode, insertIdx);
						if ( insertIdx >= 0 ) {

							currNode->SetRadius(insertIdx, promo[idx].Radius);
							currNode->SetNEntries(insertIdx, promo[idx].NObjects);

							delete promo[idx].Rep;
							promo[idx].Rep = NULL;
							idx++;
						}
						else {
							stop = true;
						}
					}
					else {
						idx++;
					}
					stop = (idx == GetNumberOfClusters()); // stop criteria
				}

				// Test if the current node is overflow
				if ( !currNode->IsOverflow() ) {
					// No, these node is not overflow

					// Is the root node?
					if (repObj != NULL) {
						// No, it isn't the root node.

						//Check, if the subRep is equal to the representative of this node
						if (repObj->IsEqual(subRep)) {
							// The representative was replaced.
							// Choose a new representative and calculate the distances.
							insertIdx = ChooseRepresentative(currNode);
							promo[0].Rep = new ObjectType();
							// Propagate the changes.
							promo[0].Rep->Unserialize(currNode->GetObject(insertIdx),
													  currNode->GetObjectSize(insertIdx));
							//UpdateDCMatrix(currNode, subTree);
							// Report the action!
							result = CHANGE_REP;
						}
						else {
							UpdateDistances(currNode, repObj, currNode->GetRepresentativeIndex());
							result =NO_ACT;
						}
					}
					else {
						// Yes, it is the root node.
						m_Header->idxRoot = currNode->GetRepresentativeIndex();
						if (m_Header->idxRoot >= 0) {
							// the representative wasn´t replaced
							repObj = new ObjectType();
							repObj->Unserialize( currNode->GetObject(m_Header->idxRoot),
												 currNode->GetObjectSize(m_Header->idxRoot));

							UpdateDistances(currNode, repObj, m_Header->idxRoot);	
							result = NO_ACT;						
							delete repObj;
							repObj = NULL;
						}
						else {
							// the representative was replaced
							// Choose a new representative and calculate the distances.
							m_Header->idxRoot = ChooseRepresentative(currNode);
							repObj = new ObjectType();
							repObj->Unserialize( currNode->GetObject(m_Header->idxRoot),
												 currNode->GetObjectSize(m_Header->idxRoot));

							delete repObj;
							repObj = NULL;
						}
						result = NO_ACT;
					}
					UpdateDCMatrix(currNode, subTree);
					//currNode->ClearMatrix();
					/////////////////////////	
					promo[0].Radius = currNode->GetMinimumRadius();
					promo[0].RootID = currNode->GetPageID();
					promo[0].NObjects = currNode->GetTotalObjectCount();								

				}
				else {
					// Yes, these node is overflow
					/////////////////////////////////////////////////////////////////////
					//promo[0].Rep = NULL;
					//promo[0].Radius = currNode->GetMinimumRadius();
					//promo[0].NObjects = currNode->GetTotalObjectCount();				
					//UpdateDistances(currNode, repObj, m_Header->idxRoot);						
					/////////////////////////////////////////////////////////////////////

					//is the root node?
					if( repObj != NULL) {
						// no it is not the root node
						/*if( repObj->IsEqual(subRep) ) {
							//The representative object was replaced

							UpdateDCMatrix(currNode, subTree);
						}*/
					}
					else {
						m_Header->idxRoot = currNode->GetRepresentativeIndex();
						/*if (m_Header->idxRoot < 0) {
							// The representative object was replaced
							UpdateDCMatrix(currNode, subTree);
						}*/					
					}//endif
					//*-**********************************************
					UpdateDCMatrix(currNode, subTree);
					//currNode->ClearMatrix();
					#ifdef __stDEBUB__
					CheckNode(currNodeID);
					#endif
					Split(currNode, promo);				
					result = PROMOTION;
				}			
				#ifdef __stDEBUB__
				CheckNode(currNodeID);
				cout << "   -after promotion\n";
				CheckDistribution(currNode);
				#endif
				break;

			case CHANGE_REP: //lack check
				//idx = 1;
				//bool stop = (idx == GetNumberOfClusters());
				#ifdef __stDEBUB__
				printf("change rep\n");
				cout << "  *****currSubTree: " << subTree << "\n";
				cout << "  -before change_rep\n";
				CheckDistribution(currNode);
				#endif

				currNode->SetEntry(	promo[0].Rep->Serialize(),
									promo[0].Rep->GetSerializedSize(),
									promo[0].RootID,
									subTree );

				currNode->GetEntry(subTree).Distance = -1.0;	//in this moment is invalid distance
				currNode->SetRadius(subTree, promo[0].Radius);
				currNode->SetNEntries(subTree, promo[0].NObjects);

				//delete promo[0].Rep;
				//promo[0].Rep = NULL;

				// Is the root node?
				if (repObj == NULL) {
					// Yes, it´s the root node.
					m_Header->idxRoot = currNode->GetRepresentativeIndex();
					if (m_Header->idxRoot >= 0) {
						// the representative wasn´t replaced
						repObj = new ObjectType();
						repObj->Unserialize( currNode->GetObject(m_Header->idxRoot),
											 currNode->GetObjectSize(m_Header->idxRoot));

						UpdateDistances(currNode, repObj, m_Header->idxRoot);	
						delete repObj;
						repObj = NULL;
					}
					else {
						// the representative was replaced
						// Choose a new representative and calculate the distances.
						m_Header->idxRoot = ChooseRepresentative(currNode);
					}					
					result = NO_ACT;
					delete promo[0].Rep;
					promo[0].Rep = NULL;
				}
				else {
					//No, it isn´t the root node
					if(repObj->IsEqual(subRep)) {
						// The representative of this node was replaced
						
						insertIdx = ChooseRepresentative(currNode);
						promo[0].Rep->Unserialize(currNode->GetObject(insertIdx), currNode->GetObjectSize(insertIdx));
						result = CHANGE_REP;
					}
					else {
						UpdateDistances(currNode, repObj, currNode->GetRepresentativeIndex());						
						result = NO_ACT;
						delete promo[0].Rep;
						promo[0].Rep = NULL;
					}
				}
				UpdateDCMatrix(currNode, subTree);
				
				#ifdef __stDEBUB__
				CheckNode(currNodeID);
				cout << "   -after change_rep\n";
				CheckDistribution(currNode);
				#endif
				//assert(currNode->GetRepresentativeIndex() >= 0);

				promo[0].Radius = currNode->GetMinimumRadius();
				promo[0].RootID = currNode->GetPageID();
				promo[0].NObjects = currNode->GetTotalObjectCount();
				
				break;
			}//end swhich
			delete subRep;
			subRep = NULL;
		}
		else {
			newSubTree.dOrepOnew = 0.0;
			// No, It isn´t a SubTree. This entry is a free Object.
			// Create a new node and grown down the tree, with the new object.
			stPage* newPage = this->NewPage();
			stMStarNode* newNode = new stMStarNode(newPage, this->GetOrder() );
			
			insertIdx = newNode->AddEntry(subRep->GetSerializedSize(), 
							  subRep->Serialize(),
							  0	);
			
			newNode->GetEntry(insertIdx).Distance = 0.0;
			newNode->SetRadius(insertIdx, 0.0);
			newNode->SetNEntries(insertIdx, 0);

			// Add the new object
			insertIdx = newNode->AddEntry(newSubTree.Rep->GetSerializedSize(),
							  newSubTree.Rep->Serialize(),
							  0);
			
			newNode->GetEntry(insertIdx).Distance = this->myMetricEvaluator->GetDistance(subRep, newSubTree.Rep);
			newNode->SetRadius(insertIdx, newSubTree.Radius);
			newNode->SetNEntries(insertIdx, newSubTree.NObjects);

			UpdateDCMatrix(newNode, insertIdx);

			currNode->SetEntry( subRep->Serialize(),
								subRep->GetSerializedSize(),
								newNode->GetPageID(),
								subTree);
			
			currNode->GetEntry(subTree).Distance = -1.0;	//in this moment is invalid distance
			currNode->SetRadius(subTree, newNode->GetMinimumRadius());
			currNode->SetNEntries(subTree, 2);
			
			// Is the root node?
			if ( repObj != NULL) {
				// No, it isn´t the root node.
				
				if( repObj->IsEqual(subRep) ) {
					idx = this->ChooseRepresentative(currNode);
					promo[0].Rep = new ObjectType;
					promo[0].Rep->Unserialize( currNode->GetObject(idx),
											   currNode->GetObjectSize(idx));

					result = CHANGE_REP;
				}
				else {
					currNode->GetEntry(subTree).Distance = this->myMetricEvaluator->GetDistance(repObj, subRep );
					result = NO_ACT;
				}
			}
			else {
				// Yes, it is the root node.
				this->m_Header->idxRoot = currNode->GetRepresentativeIndex();
				if( m_Header->idxRoot >= 0) {
					repObj = new ObjectType;
					repObj->Unserialize(currNode->GetObject(m_Header->idxRoot),
										currNode->GetObjectSize(m_Header->idxRoot));

					//***************************++ test..!!!!!!
					//currNode->GetEntry(subTree).Distance = this->myMetricEvaluator->GetDistance(repObj, subRep);
					UpdateDistances(currNode, repObj, m_Header->idxRoot);
					delete repObj;
					repObj = NULL;
				}
				else {
					m_Header->idxRoot = ChooseRepresentative(currNode);	
				}
				result = NO_ACT;
			}
			UpdateDCMatrix(currNode, subTree);

			promo[0].Radius = currNode->GetMinimumRadius();
			promo[0].RootID = currNode->GetPageID();
			promo[0].NObjects = currNode->GetNumberOfEntries();
			
			// Write node.
			this->myPageManager->WritePage(newPage);
			//clean the house
			delete newNode;
			this->myPageManager->ReleasePage(newPage);

		}		
	}
	else {
		newSubTree.dOrepOnew = 0.0;
		//No, there is a subTree that qualifies
		//Insert in this node
		#ifdef __stDEBUB__
		cout <<  "   -before add_entry\n";
		//CheckNode(currNodeID);
		CheckDistribution(currNode);
		#endif
		
		insertIdx = currNode->AddEntry( newSubTree.Rep->GetSerializedSize(),
										newSubTree.Rep->Serialize(),
										0);	
		//Is the root node?
		if (repObj == NULL) {
			// Yes, it´s the root node
			repObj = new ObjectType();
			repObj->Unserialize( currNode->GetObject(m_Header->idxRoot), 
							  currNode->GetObjectSize(m_Header->idxRoot));

			currNode->GetEntry(insertIdx).Distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
			delete repObj;
			//cout << "repIdx: " << m_Header->idxRoot << endl;
			repObj = NULL;
		}
		else {
			//No, it isn´t the root node
			currNode->GetEntry(insertIdx).Distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);		
			//(*currNode)(currNode->GetRepresentativeIndex(), insertIdx) = currNode->GetEntry(insertIdx).Distance;
			//cout << "repIdx: " << currNode->GetRepresentativeIndex() << endl;
		}

		//cout << "insertIdx: " << insertIdx << endl;
		UpdateDCMatrix(currNode, insertIdx);
		//this->PrintNode(currNode);
		
		currNode->SetRadius(insertIdx, 0.0);
		currNode->SetNEntries(insertIdx, 0);
		#ifdef __stDEBUB__
		//CheckNode(currNodeID);
		cout <<  "   -after add_entry\n";
		CheckDistribution(currNode);
		#endif

		if (currNode->IsOverflow()) {
			// Is it possible to remove the farthest object?
			if (RemoveFarthest(currNode, newSubTree, farthest)){
				// The method removed the farthest object.
				// Update the information.
				promo[0].Radius = currNode->GetMinimumRadius();
				promo[0].RootID = currNode->GetPageID();
				promo[0].NObjects = currNode->GetTotalObjectCount();
				
				// Report it to the right levels.
				if (this->IsReInsert()){
				   // The farthest object is in returnCollection.
				   result = NO_ACT;
				}else{
				   // The farthest object is in farthest.
				   result = REMOVE_FARTHEST;
				}//end if
			}
			else {
				#ifdef __stDEBUB__
				cout <<  "   -before split\n";
				CheckDistribution(currNode);
				#endif
				Split(currNode, promo);
				result = PROMOTION;
			}
		}
		else {
			promo[0].Rep = NULL;
			promo[0].Radius = currNode->GetMinimumRadius();
			promo[0].RootID = currNode->GetPageID();
			promo[0].NObjects = currNode->GetTotalObjectCount();
			result = NO_ACT;
		}
		//assert(currNode->GetRepresentativeIndex() >= 0);
	}

	this->myPageManager->WritePage(currPage);
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
	
	#ifdef __stDEBUB__
	cout << "Xend_RecInsert: check current node\n";		
	cout << " result =" << result << endl;
	CheckNode(currNodeID);
	CheckDistribution(currNodeID);
	#endif
	#ifdef __stDEBUB__
	if( result == PROMOTION){
		cout << "check distribution of promo nodes\n";
		CheckDistribution(promo[0].RootID);
		CheckDistribution(promo[1].RootID);
		cout << "check split promo nodes\n";
		CheckNode(promo[0].RootID);
		CheckNode(promo[1].RootID);
	}
	#endif

	return result;
}



template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::Split(stMStarNode* oldNode, 
												   tSubtreeInfo* promo) 
{
	#ifdef __stDEBUB__
	printf("split node\n");
	#endif

	tLogicNode * 	logicNode;		//temporal logic node
	tMSTSplitter *	mstSplitter;	//MSTsplitter
//	tMSTARNSplitter *	nSplitter;		//NClustersplitter
	stCount TotalNumOfEntries,		//
			retCollNumberOfEntries; //
	
//	stDistance prevRadius;
	int idx, idxInsert;
//	stCount idxRep; 
//	ObjectType * repObj;
//	stDistance finalRadius;
	
	stPage * newPage;
	stMStarNode * newNode;

	if (GetSplitMethod() != stMStarTree::smN_SPLIT){
		newPage = this->NewPage();
		newNode = new stMStarNode(newPage, this->GetOrder());
	}//end if

	// To use in MST_DB
	retCollNumberOfEntries = this->returnCollection->GetNumberOfEntries();

	// Calculate the total number of entries that will be use in logicNode.
	TotalNumOfEntries = oldNode->GetNumberOfEntries() + retCollNumberOfEntries; // necessary that retCollNumberOfEntries == 0???

	// For all the representatives.
	for (idx = 0; idx < this->GetNumberOfClusters(); idx++){
		if (promo[idx].Rep != NULL){
			TotalNumOfEntries++;
		}//end if
	}//end for

	// Create the new tLogicNode
	logicNode = new tLogicNode(TotalNumOfEntries);

	// update the maximum number of entries.
	this->SetMaxOccupation(oldNode->GetNumberOfEntries());
	// sets the minimum occupation of this nodes.
	logicNode->SetMinOccupation((stCount )(this->GetMaxOccupation() * this->GetMinOccupation()));

	// Add all objects from oldNode and returnCollection.
	logicNode->AddNode(oldNode);
	//logicNode->AddCollection(this->returnCollection);
	this->returnCollection->RemoveAll();

   // Add in logicNode all entries from promo.
   for (idx = 0; idx < this->GetNumberOfClusters(); idx++){
      if (promo[idx].Rep != NULL){
         idxInsert = logicNode->AddEntry(promo[idx].Rep);
         logicNode->SetEntry(idxInsert,
                               promo[idx].RootID
                             , promo[idx].NEntries
                             , promo[idx].Radius
                             );
         promo[idx].Rep = NULL;                             
      }//end if
   }//end for

	logicNode->BuildDistanceMatrix(oldNode, this->myMetricEvaluator);

	// clean before use it.
	oldNode->RemoveAll();

   //////////////////////////////////////////////////////////////////////////
   // LOGIC NODE hold, the oldNode, the promo, and returnCollection (????)
   //////////////////////////////////////////////////////////////////////////
 
	// MST Split
	//mstSplitter = new tMSTSplitter(logicNode);
	// Perform MST
	//mstSplitter->Distribute(oldNode, newNode, promo, this->myMetricEvaluator);

	#ifdef __stDEBUB__ 
	cout << "print before distributed Nodes\n";
	oldNode->PrintMatrix();
	PrintNode(oldNode);
	#endif

	this->MinMaxRadiusPromoteSlim(logicNode);
	logicNode->Distribute(oldNode, newNode, promo, this->myMetricEvaluator);
	
	#ifdef __stDEBUB__ 
	cout << "print distributed Nodes\n";
	PrintNode(oldNode);
	PrintNode(newNode);
	oldNode->PrintMatrix();
	newNode->PrintMatrix();
	#endif
	// Clean home
	//delete mstSplitter;
	// Write the new node
	this->myPageManager->WritePage(newPage);
	this->myPageManager->WritePage(oldNode->GetPage());
	delete newNode;
	this->myPageManager->ReleasePage(newPage);

	#ifdef __stDEBUB__ 
	cout << "||after distribute node \n";
	cin.get();
	CheckDistribution(promo[0].RootID);
	CheckDistribution(promo[1].RootID);
	cout << "||\n";
	#endif
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::AddNewRoot(tSubtreeInfo* promo)
{
	stPage* newPage;
	stMStarNode* newNode;
//	ObjectType* freeObject;
	int insertIdx, idxReturn, idxPromo;

	#ifdef __stDEBUB__
	if (promo[0].Rep == NULL) {
		throw invalid_argument("invalid object.");
	}
	#endif //__stDEBUB__
	
	// Now we distribute the objects.
	// Create a new node

	newPage = this->NewPage();
	newNode = new stMStarNode(newPage, this->GetOrder());
		
	for (idxPromo = 0; idxPromo < GetNumberOfClusters(); idxPromo++) {
		if (promo[idxPromo].Rep != NULL) {
			insertIdx = newNode->AddEntry(	promo[idxPromo].Rep->GetSerializedSize(),
											promo[idxPromo].Rep->Serialize(),
											promo[idxPromo].RootID
										 );
			#ifdef __stDEBUG__
			if (insertIdx < 0) {
				throw page_size_error("The page size is too small or the number of cluster is too high");
			}
			#endif
			newNode->SetRadius(insertIdx, promo[idxPromo].Radius);
			newNode->SetNEntries(insertIdx, promo[idxPromo].NObjects);	// pa ver->todavia
			
			delete promo[idxPromo].Rep;
			promo[idxPromo].Rep = NULL;
		}//end if
	}//end for

	// Get the number of objects in return Collection

	//...

	// Update the tree
	
	
	this->m_Header->idxRoot = this->ChooseRepresentative(newNode);
	
	#ifdef __stDEBUB__
	ObjectType* tmp = new ObjectType;
	ObjectType* rep = new ObjectType;
	rep->Unserialize(newNode->GetObject(m_Header->idxRoot), newNode->GetObjectSize(m_Header->idxRoot));
	for (int i=0; i< newNode->GetNumberOfEntries(); i++)
	{
		tmp->Unserialize(newNode->GetObject(i), newNode->GetObjectSize(i));
		cout << "real: " << this->myMetricEvaluator->GetDistance(tmp, rep) << " > ";
		cout << *tmp << "=> ";
		cout << newNode->GetEntry(i).Distance << "; ";
	}
	cout << endl;
	#endif

	m_Header->Height++;
	
	this->SetRoot(newPage->GetPageID());
	promo[0].Radius = newNode->GetMinimumRadius();

	this->myPageManager->WritePage(newPage);
	delete newNode;
	this->myPageManager->ReleasePage(newPage);

	#ifdef __stDEBUB__
	cout << "root node\n";
	CheckNode(GetRoot());
	#endif

}//end stMStarTree::AddNewRoot


template<class ObjectType, class EvaluatorType>
int stMStarTree<ObjectType, EvaluatorType>::ChooseSubTree(stMStarNode* node, tSubtreeInfo& newSubTree)
{
	//check id this node is real leafNode
	if (node->GetNumberOfEntries() == node->GetNumberOfFreeObjects()){
		return -1;
    }
	int subTree = -1;	// if there is not a subtree that qualifies, return -1.
	ObjectType * repObj = new ObjectType();
	stDistance minDist = Infinite();
	stCount idx, i, numberOfEntries, minOccup = MAXINT;
	stDistance distance, minDistance, minDistance2;
	stDistance * distances = new stDistance[node->GetNumberOfEntries()];
	bool stop;
	numberOfEntries = node->GetNumberOfEntries();
	minDistance = MAXDOUBLE;
	minDistance2 = MAXDOUBLE;
	
#ifdef __stDEBUB__
	int repIdx = node->GetRepresentativeIndex();
	ObjectType representiveObj;
#endif //__stDEBUB__ 

	switch (this->GetChooseMethod()) {
	case stMStarTree::cmDBHCS :
		idx = 0;
		stop = idx >= numberOfEntries;
		while (!stop) {
			if(node->IsSubTree(idx)) {
				repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
				distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
				
				if( (distance + newSubTree.Radius) <= node->GetRadius(idx) ){
					subTree = idx;
					minDistance = distance;
					stop = true;
				} 
				else if( distance + newSubTree.Radius - node->GetRadius(idx) < minDistance2 ){
					minDistance2 = distance + newSubTree.Radius - node->GetRadius(idx);
					subTree = idx;
					minDistance = distance;
					//if(  distance > (5.0/4.0)*node->GetRadius(subTree) ) {	// very low
					//	subTree = -1;
					//}
				}
			}
			idx++;
			stop = stop || idx >= numberOfEntries;
		}

		//Try to find a better subtree					
		while (idx < numberOfEntries) {
			if(node->IsSubTree(idx)) {
					
				if( newSubTree.dOrepOnew != 0.0 ){ 
					if( fabs(newSubTree.dOrepOnew - node->GetEntry(idx).Distance) <= node->GetRadius(idx) + newSubTree.Radius) {
						repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
						distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
						if( (distance + newSubTree.Radius) <= node->GetRadius(idx) &&
							(distance < minDistance)) {
							minDistance = distance;
							subTree = idx;
						}
					}
				}
				else {
					repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
					distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
					if( (distance + newSubTree.Radius) <= node->GetRadius(idx) &&
							(distance < minDistance)) {
						minDistance = distance;
						subTree = idx;
						
					}
				}
			}
			idx++;
		}//end while
		newSubTree.dOrepOnew = minDistance;
		break;
	
	case stMStarTree::cmMINDIST : /// MinGDist

         for (idx = 0; idx < node->GetNumberOfEntries(); idx++){
            // if this is a subtree entry.
            if (node->GetEntry(idx).PageID){
               // Get out the object from Node
               repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
               // Calculate the distance.
               distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
               // Find the first subtree that covers the new object.
               if ((distance < minDist) &&
                   (distance + newSubTree.Radius <= node->GetRadius(idx))) {
                  minDist = distance;             // set the distance.
                  subTree = idx;      // set the index.
               }//end if
            }//end if
         }//end for
         break; // end stDBMTree::cmMINDIST
	
	case stMStarTree::cmMINDISTWITHCOVER : 
         idx = 0;
         stop = (idx >= numberOfEntries);
         while (!stop){
            // if this entry is a subtree.
            if (node->GetEntry(idx).PageID){
               // Get out the object from Node
               repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
               // Calculate the distance.
               distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
               // Find the first subtree that covers the new object.
               if ((distance + newSubTree.Radius) <= node->GetRadius(idx)) {
                  minDistance = distance;
                  subTree = idx;       // set the index.
                  stop = true;         // stop the search.
               }else if (distance + newSubTree.Radius - node->GetRadius(idx) < minDistance) {
                  minDistance = distance + newSubTree.Radius - node->GetRadius(idx);
                  subTree = idx;
               }//end if
            }//end if
            idx++;         // Increment the counter.
            // if one of the these condicions are true, stop this while.
            stop = stop || (idx >= numberOfEntries);
         }//end while
         // Try to find a better subtree...
         while (idx < numberOfEntries) {
            // If this entry is a subtree.
            if (node->GetEntry(idx).PageID){
               // Get out the object from IndexNode.
               repObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
               // Calculate the distance.
               distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
               // Find a better subtree that covers the new object.
               if ((distance + newSubTree.Radius <= node->GetRadius(idx)) &&
                   (distance < minDistance)) {
                  minDistance = distance;
                  subTree = idx;
               }//end if
            }//end if
            idx++;         // Increment the counter.
         }//end while
         break; // end stDBMTree::cmMINDISTWITHCOVER

//	default:
//		break;
	}//end switch
	#ifdef __stDEBUB__ 
	if(subTree >= 0){
		representiveObj.Unserialize(node->GetObject(subTree), node->GetObjectSize(subTree));
		//newSubTree.dOrepOnew = this->myMetricEvaluator->GetDistance(representiveObj, newSubTree.Rep);
		//cout << "subTree: " << representiveObj->GetName() << "             dOrepOnew: " << newSubTree.dOrepOnew << "\n";
		cout << "SubTree: " << representiveObj << "\n";
		
		if( node->IsSubTree(subTree) ) {
			stPage* subTreePage = this->myPageManager->GetPage( node->GetEntry(subTree).PageID);
			stMStarNode* subTreeNode = new stMStarNode(subTreePage);
			idx = subTreeNode->GetRepresentativeIndex();
			representiveObj.Unserialize(subTreeNode->GetObject(idx), subTreeNode->GetObjectSize(idx));
			//cout << "subTreeNode[SubTree]: " << representiveObj.GetStr() << "\n";
			printf("subTreeNode[pageID]: %d\n", subTreeNode->GetPageID() );
			//cin.get();
		}
	}		
	#endif //__stDEBUG__
	delete [] distances;
	delete repObj;
	return subTree;
}


//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::MinMaxRadiusPromoteSlim(tLogicNode * node) {
   stDistance radius0, radius1;
   stDistance minRadius = MAXDOUBLE;
   stCount idx0, idx1;
   stCount i, j;
   stCount numberOfEntries = node->GetNumberOfEntries();
   tDBMMemNode * node0 = new tDBMMemNode(this->myPageManager->GetMinimumPageSize());
   tDBMMemNode * node1 = new tDBMMemNode(this->myPageManager->GetMinimumPageSize());

   // For each entry do.
   for (i = 0; i < numberOfEntries-1; i++) {
      for (j = i + 1; j < numberOfEntries; j++) {
         node->SetRepresentative(i, j);
         // Distribute
         node->TestDistribution(node0, node1, this->myMetricEvaluator);
         radius0 = node0->GetMinimumRadius();
         radius1 = node1->GetMinimumRadius();
         // Get the greatest radius.
         if (radius0 < radius1){
            radius0 = radius1;
         }//end if

         // Test if the new radius is less than the previous radius.
         if (radius0 <= minRadius) {
            minRadius = radius0;
            idx0 = i;
            idx1 = j;
         }//end if
      }//end for
   }//end for

   // Choose the representatives.
   node->SetRepresentative(idx0, idx1);
   // Clean.
   delete node0;
   delete node1;
}//end stDBMTree::MinMaxRadiusPromoteSlim

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::UpdateDistances(stMStarNode* node, ObjectType * repObj, int repObjIdx)
{
	stCount i;
	stCount numberOfEntries = node->GetNumberOfEntries();

	ObjectType * tmpObj = new ObjectType();
	
	// First test is there is a representative
	if (repObjIdx >= 0) {
		for (i = 0; i < numberOfEntries; i++ ) {
			if (i != repObjIdx) {
				tmpObj->Unserialize(node->GetObject(i), node->GetObjectSize(i));
				node->GetEntry(i).Distance = this->myMetricEvaluator->GetDistance(repObj, tmpObj);
				#ifdef __stDEBUB__ 
				cout << *repObj << "|";
				cout << *tmpObj << "; ";
				cout << node->GetEntry(i).Distance << endl;
				#endif
			} 
			else {
				//it is the representative object
				node->GetEntry(i).Distance = 0.0;
			}//end if
		}//end for
	} 
	else {
		// There is not a representative. Choose one.
		this->ChooseRepresentative(node);
	}//end if

	//clean the house before exit.
	delete tmpObj;
}

template<class ObjectType, class EvaluatorType>
stCount stMStarTree<ObjectType, EvaluatorType>::ChooseRepresentative(stMStarNode * node)
{
	stCount i, idxRep;
	stDistance newRadius = MAXDOUBLE;
	ObjectType* repObj = new ObjectType();
	stCount numberOfEntries = node->GetNumberOfEntries();

	//test what representative in the tesNode is the best for the global representative.
	for (i = 0; i < numberOfEntries; i++) {
		repObj->Unserialize(node->GetObject(i), node->GetObjectSize(i));
		// Calculate the distances.
		UpdateDistances(node, repObj, i);
		if (node->GetMinimumRadius() < newRadius) {
			newRadius = node->GetMinimumRadius();
			idxRep = i;
		}//end if
	}//end for

	// Get the best representative
	repObj->Unserialize(node->GetObject(idxRep), node->GetObjectSize(idxRep));
	// Calculate the distances to the new representative.
	UpdateDistances(node, repObj, idxRep);
	// Clean the house,
	delete repObj;
	// Return the index of the new representative.
	return idxRep;
}//end stMStarTree::ChooseRepresentative


template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::UpdateDCMatrix(stMStarNode* node, stCount idxReplacedObj)
{
	stCount i;
	ObjectType* replacedObj = new ObjectType();
	ObjectType* tmpObj = new ObjectType();
	replacedObj->Unserialize(node->GetObject(idxReplacedObj), node->GetObjectSize(idxReplacedObj));

	for (i = 0; i < node->GetNumberOfEntries(); i++) {
		if(i != idxReplacedObj ) {
			tmpObj->Unserialize( node->GetObject(i), node->GetObjectSize(i));
			(*node)(idxReplacedObj, i) = this->myMetricEvaluator->GetDistance( replacedObj, tmpObj);			
		}
	}
	delete tmpObj;
	delete replacedObj;
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::UpdateDCMatrix(stMStarNode* node)
{
	/*stCount i;
	ObjectType* replacedObj = new ObjectType();
	ObjectType* tmpObj = new ObjectType();
	replacedObj->Unserialize(node->GetObject(idxReplacedObj), node->GetObjectSize(idxReplacedObj));

	for (i = 0; i < node->GetNumberOfEntries(); i++) {
		if(i != idxReplacedObj ) {
			tmpObj->Unserialize( node->GetObject(i), node->GetObjectSize(i));
			(*node)(idxReplacedObj, i) = this->myMetricEvaluator->GetDistance( replacedObj, tmpObj);			
		}
	}

	delete tmpObj;
	delete replacedObj;*/
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::ReInsert(stMStarNode* node)
{
   ObjectType  * subTreeObj, * obj;   // For free objects.
   stDistance distance, radius;
   int idx, idxSubTree, idxRep;
   bool foundSubTree, stop;

   if (this->IsReInsert()){
      obj = new ObjectType();
      subTreeObj = new ObjectType();
      idxRep = node->GetRepresentativeIndex();

      // For each entry of node.
      for (idx = node->GetNumberOfEntries()-1; idx >= 0; idx--){
         // test if this entry is not the representative of this node.
         if (idx != idxRep){
            // If this entry is a free object or a subtree, in the last case it is
            // not possible to be the root node.
            if ((!node->GetEntry(idx).PageID) || (node->GetPageID() != this->GetRoot())){
               // Its a subtree.... What I will do?
               // Get the subtree to be test.
               obj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
               radius = node->GetRadius(idx);
               // reset variables.
               idxSubTree = 0;
               stop = (idxSubTree >= node->GetNumberOfEntries());
               foundSubTree = false;
               while (!stop){
                  // if this entry is a subtree.
                  if ((node->GetEntry(idxSubTree).PageID) && (idxSubTree != idx)){
                     // Get out the object from Node
                     subTreeObj->Unserialize(node->GetObject(idxSubTree),
                                             node->GetObjectSize(idxSubTree));
                     // Calculate the distance.
                     distance = this->myMetricEvaluator->GetDistance(subTreeObj, obj);
                     // Find a subtree that covers the new object.
                     if (distance + radius <= node->GetRadius(idxSubTree)) {
                        stop = true;         // stop the search.
                        foundSubTree = true;
                     }//end if
                  }//end if
                  idxSubTree++;         // Increment the counter.
                  // if one of the these condicions are true, stop this while.
                  stop = stop || (idxSubTree >= node->GetNumberOfEntries());
               }//end while

               // is it possible to insert in any subtrees?
               if (foundSubTree){
                  // Insert it in the top of the tree.
                  reInsertCollection->AddEntry(obj->Clone(),
                                               #ifdef __stDBMHEIGHT__
                                                  node->GetEntry(idx).Height,
                                               #endif //__stDBMHEIGHT__
                                               node->GetEntry(idx).PageID,
                                               #ifdef __stDBMNENTRIES__
                                                  node->GetNEntries(idx),
                                               #endif //__stDBMNENTRIES__
                                               radius);
                  // yes! But first remove it.
                  node->RemoveEntry(idx);
               }//end if
            }//end if
         }//end if
      }//end for

      // If this node is the root node.
      if (node->GetPageID() == this->GetRoot()){
         // Ajust the global representative index.
         m_Header->idxRoot = node->GetRepresentativeIndex();
      }//end if /**/

      delete obj;
      delete subTreeObj;
   }//end if
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::RemoveFarthest(stMStarNode* node, tSubtreeInfo& newSubTree,tSubtreeInfo& farthest)
{
	ObjectType * repObj;
	stDistance	distance, farthestDistance, finalRadius;
	stSize	farthestSize, finalSize;
	stCount	farthestIdx, numberOfEntries;
	int	insertIdx, repIdx, idx;
	bool removed = false;

	
	if( this->IsRemoveFarthest() ) {
		repIdx = node->GetRepresentativeIndex();
	    if ((repIdx >= 0) && (node->GetPageID() != this->GetRoot())){
			removed = false;
			numberOfEntries = node->GetNumberOfEntries();
			finalRadius = 0;
			
			// Get the farthest index.
			farthestIdx = node->GetFarthestObject();
			// Get the representative entry.
			repObj = new ObjectType;
			repObj->Unserialize(node->GetObject(repIdx), node->GetObjectSize(repIdx));
			// Calculate the distance form the new entry.
			distance = this->myMetricEvaluator->GetDistance(repObj, newSubTree.Rep);
			// Test if the distance is less than the radius of node
			if( distance + newSubTree.Radius <= node->GetMinimumRadius()) {
				// Test if the final radius is less than the actual.
				for (idx = 0; idx < numberOfEntries; idx++) {
					if(idx != farthestIdx) {
						if(node->GetEntry(idx).Distance + node->GetRadius(idx) > finalRadius) {
							finalRadius = node->GetEntry(idx).Distance + node->GetRadius(idx);
						}
					}
				}//end for
				// Calculate the final radius
				if ( distance + newSubTree.Radius > finalRadius) {
					finalRadius = distance + newSubTree.Radius;
				}
				// Test the final configuration.
				if(finalRadius < node->GetMinimumRadius()) {
					// Ok. The insertion of the new entry will decrease the final radius.
					// Test if there is free space to store the new entry.
					
					farthest.Rep = new ObjectType;
					// remove the farthest object.
					farthest.Rep->Unserialize(node->GetObject(farthestIdx),
											  node->GetObjectSize(farthestIdx));
					farthest.RootID = node->GetEntry(farthestIdx).PageID;
					farthest.Radius = node->GetRadius(farthestIdx);
					farthest.NObjects = node->GetNEntries(farthestIdx);
					
					farthestDistance = node->GetEntry(farthestIdx).Distance;

					node->RemoveEntry(farthestIdx);
					
					// check !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					int lasID = node->GetNumberOfEntries();
					for (int ii = farthestIdx; ii < lasID; ii++) {
						UpdateDCMatrix(node, ii);
					}
					
					if (this->IsReInsert()){
                        this->reInsertCollection->AddEntry(farthest.Rep,
                                                           #ifdef __stDBMHEIGHT__
                                                              farthest.Height,
                                                           #endif //__stDBMHEIGHT__
                                                           farthest.RootID,
                                                           //farthest.NObjects,
                                                           farthest.Radius);
                        // Now the owner is reInsertCollection.  
                        farthest.Rep = NULL;
                     }//end if
                     // Report the success.
                     removed = true;

				}
			}
			delete repObj;
		}
	}
	return removed;
}

template<class ObjectType, class EvaluatorType>
stMStarTree<ObjectType, EvaluatorType>::tResult *
	stMStarTree<ObjectType, EvaluatorType>::RangeQuery(ObjectType * sample, stDistance range)
{
	tResult* queryResult = new tResult;
	stDistance distanceRepres;
	stDistance distance;

	queryResult->SetQueryInfo(sample->Clone(), tResult::RANGEQUERY, -1, range, false);

	if(GetRoot() != 0){
		ObjectType tmpObj;
		stMStarNode* rootNode;
		stPage*	rootPage;
		rootPage = this->myPageManager->GetPage(GetRoot());
		rootNode = new stMStarNode(rootPage);
		int idxRep = m_Header->idxRoot;
		tmpObj.Unserialize(rootNode->GetObject(idxRep), rootNode->GetObjectSize(idxRep) );

		distanceRepres = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
		for (stCount i=0; i<rootNode->GetNumberOfEntries();i++) {
			if( fabs(distanceRepres - rootNode->GetEntry(i).Distance) <= range + rootNode->GetRadius(i)) {
				tmpObj.Unserialize(rootNode->GetObject(i), rootNode->GetObjectSize(i));
				if( idxRep == i)
					distance = distanceRepres;
				else
					distance = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
				if(distance <= rootNode->GetRadius(i) + range) {
					if(!rootNode->IsSubTree(i)) {
						queryResult->AddPair(tmpObj.Clone(), distance);
					}
					else {
						RangeQuery(rootNode->GetEntry(i).PageID, sample, range, distance, queryResult);
					}
				}

			}
		}
		delete rootNode;
		this->myPageManager->ReleasePage(rootPage);
	}
	return queryResult;
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::RangeQuery(stPageID currPageID, ObjectType* sample, stDistance &range, stDistance &dOrepQ, tResult *&queryResult)
{
	stMStarNode* currNode;
	stPage* currPage;
	ObjectType *tmpObj;
	stDistance dist;
	int idxRep, k;
	stDistance dOkQ = -1.0f;
	k = -1;

	currPage = this->myPageManager->GetPage(currPageID);
	currNode = new stMStarNode(currPage);

	idxRep = currNode->GetRepresentativeIndex();
	tmpObj = new ObjectType;

	for(stCount i = 0; i < currNode->GetNumberOfEntries(); i++ ) {
		if( fabs(dOrepQ - currNode->GetEntry(i).Distance ) <= range + currNode->GetRadius(i)) {
			if( CheckLemma1(currNode, i, k, dOrepQ, range, dOkQ, sample) ) {
				tmpObj->Unserialize(currNode->GetObject(i), currNode->GetObjectSize(i));
				if(i != idxRep){
					dist = this->myMetricEvaluator->GetDistance(tmpObj, sample);
				}
				else{
					dist = dOrepQ;
				}
				if( dist <= currNode->GetRadius(i) + range) {
					if( !currNode->IsSubTree(i) ) {
						queryResult->AddPair(tmpObj->Clone(), dist);
					}
					else {
						RangeQuery( currNode->GetEntry(i).PageID, sample, range, dist, queryResult);
					}
				}

			}
		}
	}
	delete tmpObj;
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
}

template<class ObjectType, class EvaluatorType>
stMStarTree<ObjectType, EvaluatorType>::tResult *stMStarTree<ObjectType, EvaluatorType>::NearestQuery(tObject * sample, stCount k, bool tie /*= false*/)
{
   tResult * result = new tResult();  // Create result
   ObjectType tmpObj;
   stPage * currPage;
   stMStarNode * currNode;
   stDistance distance, distanceRepres;
   stDistance rangeK = MAXDOUBLE;
   stCount numberOfEntries, idx;
   stCount idxRep;
   stQueryPriorityQueueValue pqCurrValue;
   stQueryPriorityQueueValue pqTmpValue;
   tDynamicPriorityQueue * queue;

   // Set information for this query
   result->SetQueryInfo(sample->Clone(), tResult::KNEARESTQUERY, k, MAXDOUBLE, tie);
   // Let's search
   if (this->GetRoot() != 0){
      // Create the Global Priority Queue.
      queue = new tDynamicPriorityQueue(STARTVALUEQUEUE, INCREMENTVALUEQUEUE);

      // Read node...
      currPage = this->myPageManager->GetPage(this->GetRoot());
      currNode = new stMStarNode(currPage);
      // Get the number of entries
      numberOfEntries = currNode->GetNumberOfEntries();
      // Rebuild the object
      tmpObj.Unserialize(currNode->GetObject(m_Header->idxRoot),
                         currNode->GetObjectSize(m_Header->idxRoot));
      // Evaluate the distance.
      distanceRepres = this->myMetricEvaluator->GetDistance(&tmpObj, sample);

      // Is there any free objects in this node?
      if (currNode->GetNumberOfFreeObjects() > 0){

         // Now do it all free objects.
         for (idx = 0; idx < numberOfEntries; idx++) {
            // tests if this is a subtree.
            if (!currNode->GetEntry(idx).PageID){
               // use of the triangle inequality to cut a subtree
               if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <= rangeK){
                  // Rebuild the object
                  tmpObj.Unserialize(currNode->GetObject(idx),
                                     currNode->GetObjectSize(idx));
	               // is it a Representative?
	               if (currNode->GetEntry(idx).Distance != 0) {
	                  // No, it is not a representative. Evaluate distance
	                  distance = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
	               }else{
	                  distance = distanceRepres;
	               }//end if

	               if (distance <= rangeK){
	                  // No, there is not a subtree. But this object qualifies.
	                  // Add the object.
	                  result->AddPair(tmpObj.Clone(), distance);
	                  // there is more than k elements?
	                  if (result->GetNumOfEntries() >= k){
	                     //cut if there is more than k elements
	                     result->Cut(k);
	                     //may I use this for performance?
	                     rangeK = result->GetMaximumDistance();
	                  }//end if
	               }//end if
               }//end if
            }//end if
         }//end for
      }//end if

      // Now do it for subtrees.
      for (idx = 0; idx < numberOfEntries; idx++) {
         // tests if this is a subtree.
         if (currNode->GetEntry(idx).PageID){
            // use of the triangle inequality to cut a subtree
            if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <=
                rangeK + currNode->GetRadius(idx)){
               // Rebuild the object
               tmpObj.Unserialize(currNode->GetObject(idx), currNode->GetObjectSize(idx));
               // is it a Representative?
               if (idx != idxRep) {
                  // No, it is not a representative. Evaluate distance
                  distance = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
               }else{
                  distance = distanceRepres;
               }//end if

               if (distance <= rangeK + currNode->GetRadius(idx)){
                  // Yes! I'm qualified! Put it in the queue.
                  pqTmpValue.PageID = currNode->GetEntry(idx).PageID;
                  pqTmpValue.Radius = currNode->GetRadius(idx);
                  // this is a subtree, put in the queue.
                  queue->Add(distance, pqTmpValue);
               }//end if
            }//end if
         }//end if
      }//end for

      // Free it all
      delete currNode;
      this->myPageManager->ReleasePage(currPage);

      // If there is something in the queue.
      if (queue->GetSize() > 0){
         this->NearestQuery(result, sample, rangeK, k, queue);
      }//end if

      // Release the Global Priority Queue.
      delete queue;
   }//end if
   return result;
}

template <class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::NearestQuery(tResult * result,
         ObjectType * sample, stDistance rangeK, stCount k,
         tDynamicPriorityQueue * queue){

   stCount idx;
   stPage * currPage;
   stMStarNode * currNode;
   ObjectType tmpObj;
   stDistance distance;
   stDistance distanceRepres = 0;
   stCount numberOfEntries;
   stQueryPriorityQueueValue pqCurrValue;
   stQueryPriorityQueueValue pqTmpValue;
   bool stop;

   queue->Get(distance, pqCurrValue);
   distanceRepres = distance;
   stDistance dOkQ;
   int kIndex = -1;


   // Let's search
   while (pqCurrValue.PageID != 0){
      // Read node...
      currPage = this->myPageManager->GetPage(pqCurrValue.PageID);
      currNode = new stMStarNode(currPage);
      // Get the number of entries
      numberOfEntries = currNode->GetNumberOfEntries();
	  //Reset values for Lemma1
	  dOkQ = -1.0f;
	  kIndex = -1;
      // Is there any free objects in this node?
      if (currNode->GetNumberOfFreeObjects() > 0){

         // Now do it all free objects.
         for (idx = 0; idx < numberOfEntries; idx++) {
            // tests if this is a subtree.
            if (!currNode->GetEntry(idx).PageID){
               // use of the triangle inequality to cut a subtree
               if( CheckLemma1(currNode, idx, kIndex, distanceRepres, rangeK, dOkQ, sample) ) {
	               if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <= rangeK){

		               // Rebuild the object.
		               tmpObj.Unserialize(currNode->GetObject(idx),
		                                  currNode->GetObjectSize(idx));
		               // is it a Representative?
		               if (currNode->GetEntry(idx).Distance != 0) {
		                  // No, it is not a representative. Evaluate distance
		                  distance = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
		               }else{
		                  distance = distanceRepres;
		               }//end if

		               if (distance <= rangeK){
		                  // No, there is not a subtree. But this object qualifies.
		                  // Add the object.
		                  result->AddPair(tmpObj.Clone(), distance);
		                  // there is more than k elements?
		                  if (result->GetNumOfEntries() >= k){
		                     //cut if there is more than k elements
		                     result->Cut(k);
		                     //may I use this for performance?
		                     rangeK = result->GetMaximumDistance();
		                  }//end if

		               }//end if
	               }//end if
			   }//end if checklemma1
            }//end if
         }//end for

      }//end if

      // Now do it for subtrees.
      for (idx = 0; idx < numberOfEntries; idx++) {
         // tests if this is a subtree.
         if (currNode->GetEntry(idx).PageID){
            // use of the triangle inequality to cut a subtree
			if( CheckLemma1(currNode, idx, kIndex, distanceRepres, rangeK, dOkQ, sample) )	{           
	            if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <=
	                rangeK + currNode->GetRadius(idx)){
	               // Rebuild the object
	               tmpObj.Unserialize(currNode->GetObject(idx), currNode->GetObjectSize(idx));
	               // is it a Representative?
	               if (currNode->GetEntry(idx).Distance != 0) {
	                  // No, it is not a representative. Evaluate distance
	                  distance = this->myMetricEvaluator->GetDistance(&tmpObj, sample);
	               }else{
	                  distance = distanceRepres;
	               }//end if

	               if (distance <= rangeK + currNode->GetRadius(idx)){
	                  // Yes! I'm qualified! Put it in the queue.
	                  pqTmpValue.PageID = currNode->GetEntry(idx).PageID;
	                  pqTmpValue.Radius = currNode->GetRadius(idx);
	                  // this is a subtree, put in the queue.
	                  queue->Add(distance, pqTmpValue);
	               }//end if
	            }//end if
			}
         }//end if
      }//end for

      // Free it all
      delete currNode;
      this->myPageManager->ReleasePage(currPage);

      // Go to next node
      stop = false;
      do{
         if (queue->Get(distance, pqCurrValue)){
            // Qualified if distance <= rangeK + radius
            if (distance <= rangeK + pqCurrValue.Radius){
               // Yes, get the pageID and the distance from the representative
               // and the query object.
               distanceRepres = distance;
               // Break the while.
               stop = true;
            }//end if
         }else{
            // the queue is empty!
            pqCurrValue.PageID = 0;
            // Break the while.
            stop = true;
         }//end if
      }while (!stop);
   }// end while

}//end stDBMTree::NearestQuery


template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::CheckLemma1(
					stMStarNode* node,const stCount &i, int &k, stDistance &dOrepQ, stDistance & radius, stDistance& dOkQ, ObjectType* query) {

    #ifdef CHECK_LEMA1
    if( k < 0) {
		k = node->FindRemote();
	}
	if ( node->at(k, i) >= 0.0 ) {
		if ( dOkQ < 0.0f) {
			ObjectType objK;
			objK.Unserialize(node->GetObject(k), node->GetObjectSize(k));
			dOkQ = this->myMetricEvaluator->GetDistance(&objK, query);
		}
        /*if ( fabs(dOkQ - node->at(k, i)) > radius + node->GetRadius(i)) {
			return false;
		}
		else {
			return true;
		}*/
        //stDistance  s_hi = node->GetEntry(k).Distance + dOrepQ,
        //            s_lo = fabs(node->GetEntry(k).Distance - dOrepQ);
        stDistance  s_hi = dOkQ + radius,
                    s_lo = dOkQ - radius;

        stDistance  r_hi = node->at(k, i) + node->GetRadius(i),
                    r_lo = node->at(k, i) - node->GetRadius(i);
        if( max(r_lo - s_hi, s_lo - r_hi) > 0.0 ) {
            return false;
        }
	}
	#endif	//CHECK_LEMA1
	return true;// 
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::Show(stPageID pageID, stCount level)
{
	stPage* currPage;
	stMStarNode* currNode;
	int  numberOfEntries;
	ObjectType* tmpObj = new ObjectType;
	int k, i;

	currPage = this->myPageManager->GetPage(pageID);
	currNode = new stMStarNode(currPage);
	numberOfEntries = currNode->GetNumberOfEntries();
	
	for (k = numberOfEntries - 1; k >= 0; k--) {
		if(currNode->IsSubTree(k))
			Show(currNode->GetEntry(k).PageID, level + 1);
		
		for (i = 0; i < level; i++) {
			cout << "       ";
		}
		if( k == numberOfEntries-1)
			printf("id = %d\n", currPage->GetPageID() );
		tmpObj->Unserialize(currNode->GetObject(k), currNode->GetObjectSize(k));
		// Object | Distance | Radius
		cout << setw(10) << *tmpObj << setw(3) << "|" << currNode->GetEntry(k).Distance << setw(3) << "|" << currNode->GetRadius(k) << "\n";
	}
	delete tmpObj;
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::CheckAllDistances(stDistance radius, stPageID pageID)
{
	stMStarNode* currNode;
	stPage* currPage;
	int numberOfEntries;
	int k, i, idxRep;
	currPage = this->myPageManager->GetPage(pageID);
	currNode = new stMStarNode( currPage );
	numberOfEntries = currNode->GetNumberOfEntries();
	
	if(radius != currNode->GetMinimumRadius() ){
		printf("RootID: %d", GetRoot() );
		printf("currId: %d", pageID );
		cout << "\nerror radius: " << radius << "-"<< currNode->GetMinimumRadius() << "\n";
		cin.get();
	}
	if( CheckNode(pageID) == false)
		return false;

	for(k = numberOfEntries - 1; k >= 0; k-- ) {
		if(currNode->IsSubTree(k)) {
			CheckAllDistances(currNode->GetRadius(k), currNode->GetEntry(k).PageID);
		}
	}
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
	return true;
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::CheckNode(stPageID pageID){
	ObjectType* tmpObj = new ObjectType;
	ObjectType* repObj = new ObjectType;
	stMStarNode* currNode;
	stPage* currPage;
	int numberOfEntries;
	int i, j, idxRep;

	currPage = this->myPageManager->GetPage(pageID);
	currNode = new stMStarNode( currPage );
	numberOfEntries = currNode->GetNumberOfEntries();
	
	if( numberOfEntries > 0) {
		//Check DCMatrix
		CheckDistribution(currNode);

		idxRep = currNode->GetRepresentativeIndex();
		repObj->Unserialize(currNode->GetObject(idxRep), currNode->GetObjectSize(idxRep));
		cout << "Rep: " << idxRep << endl;
		cout << *repObj << endl;
		if( idxRep >= 0) {
			for(i = 0; i < numberOfEntries ; i++) {
				tmpObj->Unserialize(currNode->GetObject(i), currNode->GetObjectSize(i));
				if ( this->myMetricEvaluator->GetDistance( repObj, tmpObj) != currNode->GetEntry(i).Distance ) {
					printf("distance error, in node: %d\n", pageID);
					
					std::cout << "real: " << this->myMetricEvaluator->GetDistance(repObj, tmpObj) << "\t~: " 
								  << currNode->GetEntry(i).Distance << std::endl; 

					std::cout << "idx: " << i << "\t obj: " <<  *tmpObj << std::endl;


					/*for(j = 0; j < numberOfEntries ; j++) {
						tmpObj->Unserialize(currNode->GetObject(i), currNode->GetObjectSize(i));
						std::cout << "real: " << this->myMetricEvaluator->GetDistance( repObj, tmpObj) << "\t~: " 
								  << currNode->GetEntry(j).Distance << std::endl; 

						std::cout << "idx: " << j << "\t obj: " <<  *tmpObj << std::endl;
					}*/
					cin.get();
					return false;
				}
			}
		}
		else {
			printf("No representative index, in node: %d \n", pageID);
			cin.get();
			return false;
		}
	}
	delete tmpObj;
	delete repObj;
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
	//cout << "(Y)\n";
	return true;
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::CheckDistribution(stPageID pageID)
{
	stMStarNode* node;
	stPage* currPage;
	
	currPage = this->myPageManager->GetPage(pageID);
	node = new stMStarNode( currPage );

	PrintNode(node);
	node->PrintMatrix();

	int i, j, numberOfEntries;
	ObjectType *objI, *objJ;
	objI = new ObjectType;
	objJ = new ObjectType;

	numberOfEntries = node->GetNumberOfEntries();
	cout << "numberOfEntries: " << numberOfEntries << endl;
	for (i = 0; i < numberOfEntries; i++) {
		for(j = 0; j < i; j++) {
			if( node->at(i, j) >= 0 ) {
				objI->Unserialize(node->GetObject(i), node->GetObjectSize(i));
				objJ->Unserialize(node->GetObject(j), node->GetObjectSize(j));
				if( node->at(i, j) != this->myMetricEvaluator->GetDistance(objI, objJ) ) {
					printf("nodeID =%d\n", node->GetPageID());
					printf("error, test distribution=> i=%d, j=%d\n", i, j);
					cout << *objI << " - " << *objJ << endl;
					cout << node->at(i, j) << " R: " << this->myMetricEvaluator->GetDistance(objI, objJ) << endl;
					cin.get();
					//return false;
				}		
			}
		}
	}
	
	delete node;
	this->myPageManager->ReleasePage(currPage);

	delete objI;
	delete objJ;
	return true;
}

template<class ObjectType, class EvaluatorType>
bool stMStarTree<ObjectType, EvaluatorType>::CheckDistribution(stMStarNode* node)
{
	int i, j, numberOfEntries;
	ObjectType *objI, *objJ;
	objI = new ObjectType;
	objJ = new ObjectType;
	node->PrintMatrix();
	numberOfEntries = node->GetNumberOfEntries();
	//cout << "numberOfEntries: " << numberOfEntries << endl;
	for (i = 0; i < numberOfEntries; i++) {
		for(j = 0; j < i; j++) {
			if( node->at(i, j) >= 0 ) {
				objI->Unserialize(node->GetObject(i), node->GetObjectSize(i));
				objJ->Unserialize(node->GetObject(j), node->GetObjectSize(j));
				if( node->at(i, j) != this->myMetricEvaluator->GetDistance(objI, objJ) ) {
					printf("nodeID =%d\n", node->GetPageID());
					printf("error, test distribution=> i=%d, j=%d\n", i, j);
					cout << *objI << " - " << *objJ << endl;
					cout << "dist: " << node->at(i, j) << " real dist: " << this->myMetricEvaluator->GetDistance(objI, objJ) << endl;
					cin.get();
					//return false;
				}		
			}
		}
	}
	
	delete objI;
	delete objJ;
	return true;
}

template<class ObjectType, class EvaluatorType>
void stMStarTree<ObjectType, EvaluatorType>::PrintNode(stMStarNode* node)
{

	cout << "--\n " << "nodeID: " << node->GetPageID() << endl;
	cout << "NumberOfEntries: " << node->GetNumberOfEntries() << endl;
	ObjectType objTmp;
	stCount idx;
	for (idx = 0 ; idx < node->GetNumberOfEntries(); idx++) {
		objTmp.Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
		cout << "idx: " << idx << "\t" << objTmp << endl;
	}
	cout << "--\n";

	node->PrintMatrix();
}

#endif //__MStarTree_h__
