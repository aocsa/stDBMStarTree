/* 
 * File:   stRTree.h
 * Author: aocsa
 *
 * Created on January 16, 2007, 3:07 PM
 */

#ifndef _stRTree_H
#define	_stRTree_H

#include <arboretum/stPageManager.h>
#include <arboretum/stTypes.h>
#include <arboretum/stUtil.h>
#include <arboretum/stResult.h>
#include <arboretum/stGenericPriorityQueue.h>

#include "stRNode.h"
#include "stRLogicNode.h"
#include "stSubTreeInfo.h"

#define R_ORDER(A, B) (floor(((A-NODE_HEAD_SIZE)/double(ENTRY_SIZE+B))) - 1)
// this is used to set the initial size of the dynamic queue
#define STARTVALUEQUEUE 200
// this is used to set the increment size of the dynamic queue
#define INCREMENTVALUEQUEUE 200


//=============================================================================
// Class template stRTree
//-----------------------------------------------------------------------------
/**
* @author Alexander Ocsa . (alexocsa@unsa.edu.pe)
* @todo More documentation.??
* @todo Finish the implementation.??
* @version 1.0
*/
template<class ObjectType>
class stRTree{
public:
    typedef stResult<ObjectType> tResult;
    typedef ObjectType           tObject;
	
    typedef stSubTreeInfo<ObjectType> tSubTreeInfo;

public:
    stRTree(stPageManager* pageManager);
    
    virtual   ~stRTree();    
    bool      Add(tObject* data);
	bool	  Remove(tObject* obj);
    bool	  UpdateData(tObject* oldValue, tObject* newValue);
	tResult*  IntersectionQuery(tObject* data);
    tResult*  NearestQuery(tObject * sample, stCount k, bool tie = false);
    void      Print(std::ostream& out) {
		if(GetRoot() != 0) {
			out << "----------------------------------------\n";
			this->Print(out, GetRoot(), 0);
			out << "----------------------------------------\n\n";
		}
	}
	void      Print(std::ostream& out, stPageID currPageID, int level); 

	stCount GetNumberOfObjects() {
		return HeaderInfo->ObjectCount; 
	}

protected:
    enum stInsertAction{ NO_ACT,
                         CHANGE_REP,
                         PROMOTION,
                         REMOVE_FARTHEST,
                         REMOVE_NODE,
						 NOT_FOUND
    };
	typedef stRLogicNode<ObjectType> tLogicNode;
    typedef stRPriorityQueue < stDistance, stCount > tPriorityQueue;
    typedef stDynamicRPriorityQueue < stDistance, stQueryPriorityQueueValue > tDynamicPriorityQueue;
    typedef stGenericPriorityHeap < ObjectType > tPGenericHeap;

private:
    void WriteHeader();
    void LoadHeader();
    void DefaultHeader();
    bool RecursiveUpdateData(stPageID currNodeID, tObject* oldValue, tObject* newValue, tSubTreeInfo* promo);
	int  RecursiveInsert(stPageID currNodeID, tSubTreeInfo& newSubTree, ObjectType* repObj, tSubTreeInfo* promo);
	int  RecursiveRemove(stPageID currNodeID, tObject* obj, tSubTreeInfo* promo);
  
	void AddNewRoot(tSubTreeInfo*  promo);
    void Split(stRNode* currNode, tSubTreeInfo*  promo);

	int ChooseSubTree(stRNode* node, tSubTreeInfo &newSubtree);

	void NearestQuery(tResult * result,
         ObjectType * sample, stDistance rangeK, stCount k,
         tDynamicPriorityQueue * queue);

	stPageID GetRoot() {
        return this->HeaderInfo->Root;
    }
	void SetRoot(stPageID id) {
		this->HeaderInfo->Root = id;
		this->HeaderUpdate = true;
	}
    stPage* GetNewPage() {
        this->HeaderInfo->NodeCount++;
        return this->myPageManager->GetNewPage();
    }
    stSize GetOrder() {
		return this->HeaderInfo->Order;
	}
	stSize GetNumberOfClusters() {
		return this->HeaderInfo->NumberOfClusters;
	}

private:
    
    struct stRTreeHeader {
        int			Order;
		ObjectType* TreeMBR;
		int			NumberOfClusters;
		int         SplitMethod;
        int         ChooseMethod;
        stPageID    Root;
        stCount     MaxOccupation;
        stCount     ObjectCount;
        stSize      NodeCount;
        bool        ReInsertObjects;
        stCount     Height;
    };    

public:
    enum tChooseMethod {
        ORIGINAL_RTREE_CHOOSE
    };
    enum tSplitMethod {
        ORIGINAL_RTREE_SPLIT
    };
    
    
private:
    stPageManager*	myPageManager;
    stRTreeHeader*	HeaderInfo;
    stPage*			HeaderPage;    
    bool            HeaderUpdate;
};

//-------------------------------------------------------------------------------------
template<class ObjectType>
stRTree<ObjectType>::stRTree(stPageManager* pageManager)
{
    myPageManager = pageManager;
    HeaderInfo = NULL;
    HeaderPage = NULL;
    
    LoadHeader();
    
    if( this->myPageManager->IsEmpty()) {
        DefaultHeader();
    }
    // Allocate Collection for ReInsert
}

template<class ObjectType>
stRTree<ObjectType>::~stRTree()
{
    if(this->HeaderPage != NULL) {
        if( this->HeaderInfo != NULL)
            this->WriteHeader();        
        this->myPageManager->ReleasePage(this->HeaderPage);
    }    
}

template<class ObjectType>
void stRTree<ObjectType>::WriteHeader() 
{
    if(this->HeaderUpdate) {
        this->myPageManager->WriteHeaderPage(this->HeaderPage);
        this->HeaderUpdate = false;
    }
}

template<class ObjectType>
void stRTree<ObjectType>::LoadHeader() 
{
    if( this->HeaderPage != NULL ) {
        myPageManager->ReleasePage(this->HeaderPage);
    }
    this->HeaderPage = myPageManager->GetHeaderPage();
    this->HeaderInfo = (stRTreeHeader*) this->HeaderPage->GetData();
    
    if( this->myPageManager->GetMinimumPageSize() <= sizeof(stRTreeHeader) ) {
        throw page_size_error("The Page Header size is too small");
    }
    this->HeaderUpdate = false;
}

template<class ObjectType>
void stRTree<ObjectType>::DefaultHeader() 
{
    this->HeaderPage->Clear();
	this->HeaderInfo->TreeMBR = NULL;
    this->HeaderInfo->Height = 0;
    this->HeaderInfo->ChooseMethod = 0;
    this->HeaderInfo->MaxOccupation = 0;
    this->HeaderInfo->NodeCount = 0;
    this->HeaderInfo->ObjectCount = 0;
	this->HeaderInfo->NumberOfClusters = 2;
    this->HeaderInfo->ReInsertObjects = false;
    this->HeaderInfo->Root = 0;
    this->HeaderInfo->SplitMethod = 0;
    this->HeaderUpdate = true;        
}

template<class ObjectType>
bool stRTree<ObjectType>::UpdateData(tObject* oldValue, tObject* newValue) 
{
    bool result;
    if ( this->GetRoot() == 0) {
		result = false;
    }
    else {
        
        tSubTreeInfo* promo = new tSubTreeInfo[2];
        promo[0].Rep = NULL;
        promo[1].Rep = NULL;
        
		if(! this->RecursiveUpdateData( this->GetRoot(), oldValue, newValue, promo) ) {
			result = false;
		}
		else {
			this->HeaderInfo->TreeMBR = promo[0].Rep;			
			result = true;
		}
		delete []promo;
	}
    return result;
}

template<class ObjectType>
bool stRTree<ObjectType>::RecursiveUpdateData(stPageID currNodeID, tObject* oldValue, tObject* newValue, tSubTreeInfo* promo)
{
    int idxSubTree;
    int idx;
	bool resultAction;
    stPage* currPage;
    stRNode* currNode;
	stMBR* mbr;
    ObjectType* tmpObj;
	currPage = this->myPageManager->GetPage(currNodeID);
    currNode = new stRNode(currPage);
    
	tSubTreeInfo newSubTree;
	newSubTree.Rep = oldValue;
    idxSubTree = this->ChooseSubTree(currNode, newSubTree);
    
    if( idxSubTree >= 0) {
        if( this->RecursiveUpdateData(currNode->GetEntry(idxSubTree).PageID, oldValue, newValue, promo) ) {
            currNode->SetEntry(idxSubTree, promo[0].Rep->GetSerializedSize(), promo[0].Rep->Serialize(), promo[0].RootID);
			currNode->SetNENtries(idxSubTree, promo[0].NObjects);

			tmpObj = new ObjectType();
			tmpObj->Unserialize( currNode->GetObject(0), currNode->GetObjectSize(0));

			mbr = tmpObj->Clone();
			for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
				tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
				mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
			}
			delete tmpObj;
			if( promo[0].Rep )
				delete promo[0].Rep;
			promo[0].Rep = (ObjectType*)mbr;
			promo[0].NObjects = currNode->GetTotalObjectCount();
			promo[0].RootID = currNode->GetPageID();
			resultAction = true;
		}
		else {
			resultAction = false;
        }        
    }
    else {
		tmpObj = new ObjectType();
		for (idx = 0; idx < currNode->GetNumberOfEntries(); idx++) {
			tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
			if( tmpObj->IsEqual(oldValue) ) {
#ifdef __stDEBUG__
				std::cout << "found!\n";
#endif
				break;
			}
		}
		if( idx < currNode->GetNumberOfEntries()) {
			//found
#ifdef __stDEBUG__
			std::cout << "update...idx = " << idx << "\n";

#endif		
			currNode->SetEntry(idx, newValue->GetSerializedSize(), newValue->Serialize(), 0);
			tmpObj->Unserialize(currNode->GetObject(0), currNode->GetObjectSize(0));
			mbr = tmpObj->Clone();
			for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
				tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
				mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
			}
#ifdef __stDEBUG__			
			newValue->Print(std::cout);
			std::cin.get();
#endif			
			delete tmpObj;
			promo[0].Rep = (ObjectType*)mbr;
			promo[0].NObjects = currNode->GetTotalObjectCount();
			promo[0].RootID = currNode->GetPageID();
			resultAction = true;
		}
		else {
			//!found
			resultAction = false;
		}
    }
	
	if(resultAction)
		this->myPageManager->WritePage(currPage);
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
    return resultAction;
}

template<class ObjectType>
bool	stRTree<ObjectType>::Add(ObjectType* data)
{
	int insertIdx;
    stPage* rootPage;
    stRNode* rootNode;
    
    if ( this->GetRoot() == 0) {
       	#ifdef __stDEBUG__
			std::cout << "first object\n";
		#endif

		this->HeaderInfo->Order = R_ORDER(PAGE_SIZE, data->GetSerializedSize()); 
		
		rootPage = this->GetNewPage();
        rootNode = new stRNode(rootPage, this->GetOrder());
        insertIdx = rootNode->AddEntry(data->GetSerializedSize(), data->Serialize(), 0);
		#ifdef __stDEBUG__
		if(insertIdx < 0) {
			throw page_size_error("The page size is too small to store the first object");
		}
		#endif // __stDEBUG__
		rootNode->GetEntry(0).PageID = 0;
		
		this->SetRoot(rootPage->GetPageID());
		this->HeaderInfo->Height = 1;

		this->myPageManager->WritePage(rootPage);
		delete rootNode;
		this->myPageManager->ReleasePage(rootPage);
    }
    else {
        tSubTreeInfo subTree;
        subTree.Rep = data;
        subTree.Height = 0;
        subTree.NObjects = 0;
        subTree.RootID = 0;
        
        tSubTreeInfo* promo = new tSubTreeInfo[2];
        promo[0].Rep = NULL;
        promo[1].Rep = NULL;
        
		#ifdef __stDEBUG__
			std::cout << "first, recursive insert\n";
		#endif
        if( PROMOTION == this->RecursiveInsert( this->GetRoot(), subTree, NULL, promo) ){
            this->AddNewRoot(promo);       //this->HeaderInfo->Height++;
            this->HeaderUpdate = true;
        }
		this->HeaderInfo->TreeMBR = promo[0].Rep;			
		delete []promo;
	}
	this->HeaderInfo->ObjectCount++;
    return true;
}


template<class ObjectType>
int stRTree<ObjectType>::RecursiveInsert(stPageID currNodeID, tSubTreeInfo& newSubTree, ObjectType* repObj, tSubTreeInfo* promo)
{
    int idxSubTree, insertIdx;
    int idx, resultAction;
    ObjectType* subTreeObj;
    stPage* currPage;
    stRNode* currNode;
	stMBR* mbr;
    ObjectType* tmpObj;
	currPage = this->myPageManager->GetPage(currNodeID);
    currNode = new stRNode(currPage);
    
    idxSubTree = this->ChooseSubTree(currNode, newSubTree);
    
    if( idxSubTree >= 0) {
        subTreeObj = new ObjectType();
        subTreeObj->Unserialize(newSubTree.Rep->Serialize(), newSubTree.Rep->GetSerializedSize());
        
		#ifdef __stDEBUG__
			std::cout << "recursive insert\n";
		#endif
        switch( this->RecursiveInsert(currNode->GetEntry(idxSubTree).PageID, newSubTree, subTreeObj, promo) ) {
            case NO_ACT:
				#ifdef __stDEBUG__
					std::cout << "update\n";
				#endif
				currNode->SetEntry(idxSubTree, promo[0].Rep->GetSerializedSize(), promo[0].Rep->Serialize(), promo[0].RootID);
				currNode->SetNENtries(idxSubTree, promo[0].NObjects);

				tmpObj = new ObjectType();
				tmpObj->Unserialize( currNode->GetObject(0), currNode->GetObjectSize(0));

				mbr = tmpObj->Clone();
				for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
					tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
					mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
				}
				delete tmpObj;
				if( promo[0].Rep )
					delete promo[0].Rep;
				promo[0].Rep = (ObjectType*)mbr;
				promo[0].NObjects = currNode->GetTotalObjectCount();
				promo[0].RootID = currNode->GetPageID();
				resultAction = NO_ACT;
				break;

            case PROMOTION:
				#ifdef __stDEBUG__
					std::cout << "promotion\n";
				#endif
				bool stop;
				
				idx = 0;
				currNode->SetEntry( idxSubTree, promo[idx].Rep->GetSerializedSize(),
														promo[idx].Rep->Serialize(),							
														promo[idx].RootID);
				currNode->SetNENtries(idxSubTree, promo[idx].NObjects);
				
				delete promo[idx].Rep;
				promo[idx].Rep = NULL;
				idx++;
				stop = (idx == this->GetNumberOfClusters());
				while (!stop) {
					if(promo[idx].Rep != NULL) {
						insertIdx = currNode->AddEntry(promo[idx].Rep->GetSerializedSize(),
														promo[idx].Rep->Serialize(),							
														promo[idx].RootID);
						if(insertIdx < 0) {
							stop = true;
						}
						else {
							currNode->SetNENtries(insertIdx, promo[idx].NObjects);

							delete promo[idx].Rep;
							promo[idx].Rep = NULL;
						}
					}
					idx++;
					stop = (stop  || idx == this->GetNumberOfClusters());
				}
				if( currNode->IsOverflow()) {
					this->Split(currNode, promo);
					resultAction = PROMOTION;
				}
				else {
					tmpObj = new ObjectType();
					tmpObj->Unserialize( currNode->GetObject(0), currNode->GetObjectSize(0));
					mbr = tmpObj->Clone();
					for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
						tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
						mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
					}
					delete tmpObj;
					if( promo[0].Rep )
						delete promo[0].Rep;
					promo[0].Rep = (ObjectType*)mbr;
					promo[0].NObjects = currNode->GetTotalObjectCount();
					promo[0].RootID = currNode->GetPageID();
					resultAction = NO_ACT;
				}
				break;
            //case 
        }
        
    }
    else {
		#ifdef __stDEBUG__
			std::cout << "add object\n";
		#endif
        insertIdx = currNode->AddEntry(newSubTree.Rep->GetSerializedSize(), newSubTree.Rep->Serialize(), 0);
		currNode->SetNENtries(insertIdx, 0);
		
		if( currNode->IsOverflow()) {
			this->Split(currNode, promo);
			resultAction = PROMOTION;
		}
		else {
			tmpObj = new ObjectType();
			tmpObj->Unserialize( currNode->GetObject(0), currNode->GetObjectSize(0));

			mbr = tmpObj->Clone();
			for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
				tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
				mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
			}
			delete tmpObj;
			promo[0].Rep = (ObjectType*)mbr;
			promo[0].NObjects = currNode->GetTotalObjectCount();
			promo[0].RootID = currNode->GetPageID();
			resultAction = NO_ACT;
		}
    }
	
	#ifdef __stDEBUG__
			std::cout << "resultAction "<< resultAction << "\n";
	#endif
	this->myPageManager->WritePage(currPage);
	delete currNode;
	this->myPageManager->ReleasePage(currPage);

    return resultAction;
}

template<class ObjectType>
void stRTree<ObjectType>::AddNewRoot(tSubTreeInfo* promo)
{
	int idx, insertIdx;
	stPage* rootPage;
	stRNode* rootNode;
	
	rootPage = this->GetNewPage();
	rootNode = new stRNode(rootPage, this->GetOrder());

	for (idx = 0; idx < this->GetNumberOfClusters(); idx++) {
		if(promo[idx].Rep) {
			insertIdx = rootNode->AddEntry(promo[idx].Rep->GetSerializedSize(), promo[idx].Rep->Serialize(), promo[idx].RootID);
			rootNode->SetNENtries(insertIdx, promo[idx].NObjects);
			
			delete promo[idx].Rep;
			promo[idx].Rep = NULL;
		}
	}
	
	this->HeaderInfo->Height++;
	this->SetRoot(rootPage->GetPageID());		

	ObjectType* tmpObj = new ObjectType();
	tmpObj->Unserialize( rootNode->GetObject(0), rootNode->GetObjectSize(0));

	stMBR* mbr = tmpObj->Clone();
	for (idx = 1; idx < rootNode->GetNumberOfEntries(); idx++) {
		tmpObj->Unserialize( rootNode->GetObject(idx), rootNode->GetObjectSize(idx));
		mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
	}
	delete tmpObj;
	promo[0].Rep = (ObjectType*)mbr;
	this->myPageManager->WritePage(rootPage);
	delete rootNode;
	this->myPageManager->ReleasePage(rootPage);		
}


template<class ObjectType>
void stRTree<ObjectType>::Split(stRNode* oldNode,tSubTreeInfo*  promo)
{
	stPage* newPage;
	stRNode* newNode;
	tLogicNode* logicNode = new tLogicNode( oldNode->GetNumberOfEntries() );
	
	newPage = this->GetNewPage();
	newNode = new stRNode(newPage, GetOrder());

	logicNode->AddNode(oldNode);
	
	oldNode->RemoveAll();
	
	logicNode->Distribute(oldNode, newNode, promo);

	this->myPageManager->WritePage(oldNode->GetPage());///????
	this->myPageManager->WritePage(newPage);
	delete newNode;
	this->myPageManager->ReleasePage(newPage);
}


template<class ObjectType>
int stRTree<ObjectType>::ChooseSubTree(stRNode* node, tSubTreeInfo &newSubtree)
{
	if(node->GetNumberOfEntries() == node->GetNumberOfFreeObjects() )
		return -1;
    int subTree = -1;
    int i;
    stDistance increased;
    stDistance min = MAXDOUBLE;
    ObjectType* tmpObj = new ObjectType();
	for (i = 0; i < node->GetNumberOfEntries(); i++) {
		tmpObj->Unserialize(node->GetObject(i), node->GetObjectSize(i));
		stMBR* a = tmpObj->GetUnionMBR( newSubtree.Rep );
		increased = a->GetArea() - tmpObj->GetArea();
		//increased = tmpObj->IncreaseRequired(newSubtree->Rep);
        if( increased < min ) {
            min = increased;
            subTree = i;
        }
		delete a;
    }
	delete tmpObj;
    return subTree;
}

template<class ObjectType>
void stRTree<ObjectType>::Print(std::ostream& out, stPageID currPageID, int level) 
{
	int idx;
	stPage* currPage;
	stRNode* currNode;
	ObjectType* tmpObj = new ObjectType;
	currPage = this->myPageManager->GetPage(currPageID);
	currNode = new stRNode(currPage);
	//out << "*" << currNode->GetNumberOfEntries() << "*\n";
	for (idx = currNode->GetNumberOfEntries() - 1; idx >= 0; idx--) {
		
		if(currNode->GetEntry(idx).PageID) {
			this->Print(out, currNode->GetEntry(idx).PageID, level + 1);
		}
		tmpObj->Unserialize(currNode->GetObject(idx), currNode->GetObjectSize(idx));
		
		for (int i = 0; i < DIMENSION;i++) {
			for (int k = 0; k < level ; k++) {
				out << "        ";
			}
			out << tmpObj->GetBegin(i) << " - " << tmpObj->GetEnd(i) << "\n";
		}
		for (int k = 0; k < level ; k++) {
			out << "        ";
		}
		out << tmpObj->GetOID() << "|\n";
		out << "\n";
		//out << << ;
	}
	delete tmpObj;
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
}

template<class ObjectType>
bool stRTree<ObjectType>::Remove(tObject* obj)
{
	bool result;
    if ( this->GetRoot() == 0) {
		result = false;
    }
    else {
        
        tSubTreeInfo* promo = new tSubTreeInfo[2];
        promo[0].Rep = NULL;
        promo[1].Rep = NULL;
        
		if( this->RecursiveRemove( this->GetRoot(), obj, promo) == NOT_FOUND) {
			result = false;
		}
		else {
			this->HeaderInfo->TreeMBR = promo[0].Rep;			
			result = true;
		}
		delete []promo;
	}
    return result;
}

template<class ObjectType>
int stRTree<ObjectType>::RecursiveRemove(stPageID currPageID, tObject* obj, tSubTreeInfo* promo)
{
    int idxSubTree;
    int idx;
	int resultAction;
    stPage* currPage;
    stRNode* currNode;
	stMBR* mbr;
    ObjectType* tmpObj;
	currPage = this->myPageManager->GetPage(currPageID);
    currNode = new stRNode(currPage);
    
	tSubTreeInfo newSubTree;
	newSubTree.Rep = obj;
    idxSubTree = this->ChooseSubTree(currNode, newSubTree);
    
    if( idxSubTree >= 0) {
        switch( this->RecursiveRemove(currNode->GetEntry(idxSubTree).PageID, obj, promo) ) {
		case NO_ACT:
            currNode->SetEntry(idxSubTree, promo[0].Rep->GetSerializedSize(), promo[0].Rep->Serialize(), promo[0].RootID);
			currNode->SetNENtries(idxSubTree, promo[0].NObjects);

			tmpObj = new ObjectType();
			tmpObj->Unserialize( currNode->GetObject(0), currNode->GetObjectSize(0));

			mbr = tmpObj->Clone();
			for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
				tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
				mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
			}
			delete tmpObj;
			if( promo[0].Rep )
				delete promo[0].Rep;
			promo[0].Rep = (ObjectType*)mbr;
			promo[0].NObjects = currNode->GetTotalObjectCount();
			promo[0].RootID = currNode->GetPageID();
			resultAction = NO_ACT;
			break;
		case REMOVE_NODE:
			currNode->RemoveEntry(idxSubTree);
			if( currNode->GetNumberOfEntries() == 0) {
				resultAction = REMOVE_NODE;
			}
			else {
				tmpObj = new ObjectType();
				tmpObj->Unserialize(currNode->GetObject(0), currNode->GetObjectSize(0));
				mbr = tmpObj->Clone();
				for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
					tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
					mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
				}
				delete tmpObj;
				promo[0].Rep = (ObjectType*)mbr;
				promo[0].NObjects = currNode->GetTotalObjectCount();
				promo[0].RootID = currNode->GetPageID();
				resultAction = NO_ACT;
			}			
			break;
		case NOT_FOUND:
			resultAction = NOT_FOUND;        
		}        
    }
    else {
		tmpObj = new ObjectType();
		for (idx = 0; idx < currNode->GetNumberOfEntries(); idx++) {
			tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
			if( tmpObj->IsEqual(obj) ) {
#ifdef __stDEBUG__
				std::cout << "found!\n";
#endif
				break;
			}
		}
		if( idx < currNode->GetNumberOfEntries()) {
			//found
			currNode->RemoveEntry(idx);
			if( currNode->GetNumberOfEntries() == 0) {
				resultAction = REMOVE_NODE;
			}
			else {
				tmpObj->Unserialize(currNode->GetObject(0), currNode->GetObjectSize(0));
				mbr = tmpObj->Clone();
				for (idx = 1; idx < currNode->GetNumberOfEntries(); idx++) {
					tmpObj->Unserialize( currNode->GetObject(idx), currNode->GetObjectSize(idx));
					mbr = mbr->GetUnionMBR( (stMBR*)tmpObj );
				}
				delete tmpObj;
				promo[0].Rep = (ObjectType*)mbr;
				promo[0].NObjects = currNode->GetTotalObjectCount();
				promo[0].RootID = currNode->GetPageID();
				resultAction = NO_ACT;
			}
		}
		else {
			//!found
			resultAction = NOT_FOUND;
		}
    }
	
	if(resultAction != NOT_FOUND)
		this->myPageManager->WritePage(currPage);
	delete currNode;
	this->myPageManager->ReleasePage(currPage);
    return resultAction;
}

template<class ObjectType>
stResult<ObjectType>*  stRTree<ObjectType>::IntersectionQuery(tObject* data) 
{

	return NULL;
}

template<class ObjectType>
stResult<ObjectType>*  stRTree<ObjectType>::NearestQuery(tObject * sample, stCount k, bool tie )
{
   tResult * result = new tResult();  // Create result
   ObjectType tmpObj;
   stPage * currPage;
   stRNode * currNode;
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
      currNode = new stRNode(currPage);
      // Get the number of entries
      numberOfEntries = currNode->GetNumberOfEntries();
      // Rebuild the object
      //tmpObj.Unserialize(HeaderInfo->TreeMBR->Serialize(),
      //                   HeaderInfo->TreeMBR->GetSerializedSize());
      // Evaluate the distance.
      distanceRepres = MAXDOUBLE;

      // Is there any free objects in this node?
      if (currNode->GetNumberOfFreeObjects() > 0){
         // Now do it all free objects.
         for (idx = 0; idx < numberOfEntries; idx++) {
            // tests if this is a subtree.
            if (!currNode->GetEntry(idx).PageID) {
               // use of the triangle inequality to cut a subtree
               //if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <= rangeK){
                  // Rebuild the object
                  tmpObj.Unserialize(currNode->GetObject(idx),
                                     currNode->GetObjectSize(idx));
	               // is it a Representative?
	               //if (currNode->GetEntry(idx).Distance != 0) {
	                  // No, it is not a representative. Evaluate distance
	                  distance = tmpObj.GetMinDist(sample);
	               //}else{
	               //   distance = distanceRepres;
	               //}//end if

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
               //}//end if
            }//end if
         }//end for
      }//end if

      // Now do it for subtrees.
      for (idx = 0; idx < numberOfEntries; idx++) {
         // tests if this is a subtree.
         if (currNode->GetEntry(idx).PageID){
            // use of the triangle inequality to cut a subtree
            //if (fabs(distanceRepres - currNode->GetEntry(idx).Distance) <=
              //  rangeK + currNode->GetRadius(idx)){
               // Rebuild the object
               tmpObj.Unserialize(currNode->GetObject(idx), currNode->GetObjectSize(idx));
               // is it a Representative?
               if (idx != idxRep) {
                  // No, it is not a representative. Evaluate distance
                  distance = tmpObj.GetMinDist( sample);
               }else{
                  distance = distanceRepres;
               }//end if

               if (distance <= rangeK /*+ currNode->GetRadius(idx)*/){
                  // Yes! I'm qualified! Put it in the queue.
                  pqTmpValue.PageID = currNode->GetEntry(idx).PageID;
                  //pqTmpValue.Radius = currNode->GetRadius(idx);
                  // this is a subtree, put in the queue.
                  queue->Add(distance, pqTmpValue);
               }//end if
            //}//end if
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

template <class ObjectType>
void stRTree<ObjectType>::NearestQuery(tResult * result,
         ObjectType * sample, stDistance rangeK, stCount k,
         tDynamicPriorityQueue * queue){

   stCount idx;
   stPage * currPage;
   stRNode * currNode;
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
   tObject h;
   int kIndex = -1;

   // Let's search
   while (pqCurrValue.PageID != 0){
      // Read node...
      currPage = this->myPageManager->GetPage(pqCurrValue.PageID);
      currNode = new stRNode(currPage);
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
               tmpObj.Unserialize(currNode->GetObject(idx),
		                          currNode->GetObjectSize(idx));
		       distance = tmpObj.GetMinDist(sample);
		       if (distance <= rangeK) {
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
         }//end for

      }//end if

      // Now do it for subtrees.
      for (idx = 0; idx < numberOfEntries; idx++) {
         // tests if this is a subtree.
         if (currNode->GetEntry(idx).PageID){
			   tmpObj.Unserialize(currNode->GetObject(idx), currNode->GetObjectSize(idx));
  			   distance = tmpObj.GetMinDist(sample);
 
			   if (distance <= rangeK /*+ currNode->GetRadius(idx)*/){
				  pqTmpValue.PageID = currNode->GetEntry(idx).PageID;
				  queue->Add(distance, pqTmpValue);
			   }//end if
		}//end if
      }//end for

      // Free it all
      delete currNode;
      this->myPageManager->ReleasePage(currPage);

      // Go to next node
      stop = false;
      do{
         if (queue->Get(distance, pqCurrValue)){
            // Qualified if distance <= rangeK 
            if (distance <= rangeK ){
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

#endif	/* _stRTree_H */
