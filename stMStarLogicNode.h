#ifndef __stMStarLogicNode__
#define __stMStarLogicNode__

#include "arboretum/stDBMNode.h"
#include "MStarNode.h"
	
template<class ObjectType, class EvaluatorType>
class stMStarTree;

template<class ObjectType, class EvaluatorType>
class stMStarLogicNode {
public:
	typedef stGenericMatrix<stDistance> tDistanceMatrix;
	typedef stMStarTree<ObjectType, EvaluatorType>::stSubtreeInfo tSubtreeInfo;
	typedef stDBMMemNode < ObjectType > tDBMMemNode;
	
	/**
	* Creates a new instance of this node with no object
	* @param maxOccupation The maximum number of entries.
	*/
	stMStarLogicNode(stCount maxOccupation);
	~stMStarLogicNode();
	
	/**
	* Adds an object to this node. this method will claim the ownership
	* of the object instance.
	*/
	stCount AddEntry(ObjectType* obj);
	
	int AddEntry(stSize size, const stByte* object);
	stCount GetNumberOfEntries() {
		return Count;
	}
	ObjectType* GetObject(stCount idx) {
		return Entries[idx].Object;
	}

	ObjectType* operator [] (stCount idx) {
		return Entries[idx].Object;
	}

	stPageID GetPageID(stCount idx) {
		return Entries[idx].PageID;
	}
	stCount GetNEntries(stCount idx) {
		return Entries[idx].NEntries;
	}
	stDistance GetRadius(stCount idx) {
		return Entries[idx].Radius;
	}
	stCount GetNumberOfFreeObjects();

	void SetEntry(stCount idx, stPageID pageID, stCount nEntries, stDistance radius);
	void AddNode(stMStarNode* node);
	
	stCount GetRepresentativeIndex(stCount idx){
		return this->RepIndex[idx];
	}
	ObjectType* GetRepresentative(stCount idx) {
		return Entries[RepIndex[idx]].Object;
	}
	void SetRepresentative(stCount rep0, stCount rep1) {
		this->RepIndex[0] = rep0;
		this->RepIndex[1] = rep1;
	}
	

	void Distribute(stMStarNode* node0, stMStarNode* node1, tSubtreeInfo* promo, EvaluatorType* metricEvaluator);
	
	void SetMinOccupation(stCount min) {
		this->MinOccupation = min;

		if ( (this->MinOccupation > (this->MaxEntries/2)) || (MinOccupation == 0) ) {
			this->MinOccupation = 2;
		}
	}
	
	bool IsRepresentative(stCount idx) {
		return (idx == this->RepIndex[0]) || (idx == this->RepIndex[1]);
	}
	/**
	* Gets the ownership of an object associated with a given entry
	* This method will avoid the automatic destruction of the object
	* instance by the destructor of this node.
	*
    * <p> This method can be used to buy the representative object to avoid
	* unnecessary replications
	*/ 
	ObjectType* BuyObject(stCount idx) {
		Entries[idx].Mine = false;
		return Entries[idx].Object;
	}

	stCount BuildDistanceMatrix(stMStarNode* node, EvaluatorType * metricEvaluator);
	void	TestDistribution(tDBMMemNode * node0, tDBMMemNode * node1,
         EvaluatorType * metricEvaluator);
	void MaxDistancePromote();

private:
	struct stMStarLogicEntry {
		ObjectType* Object;
		stPageID	PageID;
		stCount		NEntries;
		stDistance	Radius;
		stDistance	Distance[2];
		bool		Mine;
		bool		Mapped;
	};

	stCount			  MinOccupation;
	stCount			  MaxEntries;
	stMStarLogicEntry* Entries;
	stCount			  Count;
	stCount			  RepIndex[2];
	//tDistanceMatrix	  DMat;
	
	stCount UpdateDistances(EvaluatorType* metricEvaluator);
public:
	tDistanceMatrix	  DMat;
};

#include <algorithm>

template<class ObjectType, class EvaluatorType>
stMStarLogicNode<ObjectType, EvaluatorType>::stMStarLogicNode(stCount maxOccupation)
{
	this->MaxEntries = maxOccupation;
	this->Entries = new stMStarLogicEntry[MaxEntries];

	this->RepIndex[0] = 0;
	this->RepIndex[0] = 0;

	this->Count = 0;
	this->MinOccupation = (stCount)(0.25*MaxEntries);
	if ( (MinOccupation > MaxEntries/2) || (MinOccupation == 0) ) {
		MinOccupation = 2;
	}
	
	this->DMat.SetSize(MaxEntries, MaxEntries);
}

template<class ObjectType, class EvaluatorType>
stMStarLogicNode<ObjectType, EvaluatorType>::~stMStarLogicNode()
{

	if (Entries != NULL) {
		for (int idx = 0; idx < MaxEntries; idx++) {
			if ( (Entries[idx].Object != NULL) && (Entries[idx].Mine == true) ) {
				delete Entries[idx].Object;
			}
		}
	}
	this->Count = 0;
	delete [] Entries;
}


template<class ObjectType, class EvaluatorType>
stCount stMStarLogicNode<ObjectType, EvaluatorType>::AddEntry(ObjectType* obj)
{
	this->Entries[Count].Object = obj;
	this->Entries[Count].Mine = true;
	++Count;
	return Count - 1;
}

template<class ObjectType, class EvaluatorType>
int stMStarLogicNode<ObjectType, EvaluatorType>::AddEntry(stSize size, const stByte* object)
{
	if (this->Count < MaxEntries){
		Entries[Count].Object = new ObjectType();
		Entries[Count].Object->Unserialize(object, size);
		Entries[Count].Mine = true;
		++Count;
		return Count - 1;
	}
	else {
		return -1;
	}
			
}

template<class ObjectType, class EvaluatorType>
stCount stMStarLogicNode<ObjectType, EvaluatorType>::GetNumberOfFreeObjects()
{
	stCount idx;
	stCount count = 0;
	for (idx = 0; idx < GetNumberOfEntries(); idx++) 	{
		if ( !this->Entries[idx].PageID ){
			++count;
		}
	}
	return count;
}

template<class ObjectType, class EvaluatorType>
void stMStarLogicNode<ObjectType, EvaluatorType>::SetEntry(stCount idx, stPageID pageID, stCount nEntries, stDistance radius)
{
	this->Entries[idx].PageID = pageID;
	this->Entries[idx].NEntries = nEntries;
	this->Entries[idx].Radius = radius;

}

template<class ObjectType, class EvaluatorType>
void stMStarLogicNode<ObjectType, EvaluatorType>::AddNode(stMStarNode* node)
{
	stCount idx;
	#ifdef __stDEBUG__
	if( this->Count + node->GetNumberOfEntries() > this->MaxEntries ) {
		throw invalid_argument("Insuficient space to store the node ");
	}
	#endif
	for (idx = 0; idx < node->GetNumberOfEntries(); idx++) {
		AddEntry(node->GetObjectSize(idx), node->GetObject(idx));
		this->Entries[idx].Radius = node->GetRadius(idx);
		this->Entries[idx].NEntries = node->GetNEntries(idx);
		this->Entries[idx].PageID = node->GetEntry(idx).PageID;
	}
}

template<class ObjectType, class EvaluatorType>
stCount stMStarLogicNode<ObjectType, EvaluatorType>::BuildDistanceMatrix(stMStarNode* node, EvaluatorType * metricEvaluator)
{
	for (int i = 0; i < this->Count; i++)	{
		DMat[i][i] = 0;
      	for (int j = 0; j < i; j++) {
			if( node->at(i, j) < 0) {
				DMat[i][j] = metricEvaluator->GetDistance(GetObject(i), GetObject(j));
			}
			else {
				#ifdef __stDEBUB__
				if ( metricEvaluator->GetDistance(GetObject(i), GetObject(j))  != node->at(i,j) ) {
					printf("error builtDCMatrix, node: %d\n", node->GetPageID() ); 
					cout << node->GetRepresentativeIndex() << endl;
					printf("i=%d, j=%d\n", i, j);
					cin.get();

				}				
				#endif
				DMat[i][j] = node->at(i, j);
			}
			DMat[j][i] = DMat[i][j];
		}		
	}
	return  (this->Count * (this->Count - 1) )/2;//(N*(N-1))/2
}

template<class ObjectType, class EvaluatorType>
void stMStarLogicNode<ObjectType, EvaluatorType>::MaxDistancePromote()
{
	
}

//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
void stMStarLogicNode<ObjectType, EvaluatorType>::Distribute(
            stMStarNode * node0, stMStarNode * node1,
            tSubtreeInfo * promo, EvaluatorType * metricEvaluator){
	

	int i, j;
	int idxRep0, idxRep1;
	int idx;
	int idx0, idx1;
	int currObj;
	stDistanceIndex * distanceIndex0,* distanceIndex1;
	std::vector<int> cluster[2];
		
	idxRep0 = GetRepresentativeIndex(0);
	idxRep1 = GetRepresentativeIndex(1);
	
	distanceIndex0 = new stDistanceIndex[this->Count];
	distanceIndex1 = new stDistanceIndex[this->Count];

	for (i=0; i < this->Count; i++) {
		distanceIndex0[i].Index = i;
		distanceIndex0[i].Distance = DMat[i][idxRep0];
		distanceIndex1[i].Index = i;
		distanceIndex1[i].Distance = DMat[i][idxRep1];
		Entries[i].Mapped = false;
		Entries[i].Mine = true;
	}

	//Sorting by distance...
	sort(distanceIndex0, distanceIndex0 + this->Count);
	sort(distanceIndex1, distanceIndex1 + this->Count);

	// Make one of then get the minimum occupation.
	idx0 = idx1 = 0;

	// FIns a candidate for node 1
	while ( Entries[distanceIndex0[idx0].Index].Mapped) {
		idx0++;
	}
	// Add to node 1
	currObj = distanceIndex0[idx0].Index;
	Entries[currObj].Mapped = true;

	cluster[0].push_back(currObj);
	idx = node0->AddEntry(Entries[currObj].Object->GetSerializedSize(),
                            Entries[currObj].Object->Serialize(),
                            Entries[currObj].PageID);
	node0->GetEntry(idx).Distance = distanceIndex0[idx0].Distance;
    node0->SetNEntries(idx, Entries[currObj].NEntries);
    node0->SetRadius(idx, Entries[currObj].Radius);
    
	#ifdef __stDBMHEIGHT__
         node0->GetEntry(idx).Height = Entries[currObj].Height;
    #endif //__stDBMHEIGHT__


	// Find a candidate for node 2
	while (Entries[distanceIndex1[idx1].Index].Mapped){
		idx1++;
	}//end while
	  
	currObj = distanceIndex1[idx1].Index;
	Entries[currObj].Mapped = true;

	cluster[1].push_back(currObj);
	idx = node1->AddEntry(Entries[currObj].Object->GetSerializedSize(),
						Entries[currObj].Object->Serialize(),
						Entries[currObj].PageID);
	node1->GetEntry(idx).Distance = distanceIndex1[idx1].Distance;
	node1->SetNEntries(idx, Entries[currObj].NEntries);
	node1->SetRadius(idx, Entries[currObj].Radius);
	#ifdef __stDBMHEIGHT__
	 node1->GetEntry(idx).Height = Entries[currObj].Height;
	#endif //__stDBMHEIGHT__

	//Distribute the others.
	for (i = 0; i < this->Count; i++) {
		if(Entries[i].Mapped == false) {
			Entries[i].Mapped = true;

			if(DMat[i][idxRep0] < DMat[i][idxRep1]){
				cluster[0].push_back(i);
				idx = node0->AddEntry(Entries[i].Object->GetSerializedSize(),
									  Entries[i].Object->Serialize(),
									  Entries[i].PageID);
				if (idx >= 0){
					node0->GetEntry(idx).Distance = DMat[i][idxRep0];
					node0->SetNEntries(idx, Entries[i].NEntries);
				    node0->SetRadius(idx, Entries[i].Radius);
				    #ifdef __stDBMHEIGHT__
					  node0->GetEntry(idx).Height = Entries[i].Height;
				    #endif //__stDBMHEIGHT__
				}else {
				
				}

			}
			else {
				cluster[1].push_back(i);
				idx = node1->AddEntry(Entries[i].Object->GetSerializedSize(),
									  Entries[i].Object->Serialize(),
									  Entries[i].PageID);
				if (idx >= 0){
					node1->GetEntry(idx).Distance = DMat[i][idxRep1];
				    node1->SetNEntries(idx, Entries[i].NEntries);
				    node1->SetRadius(idx, Entries[i].Radius);
				    #ifdef __stDBMHEIGHT__
					  node1->GetEntry(idx).Height = Entries[i].Height;
				    #endif //__stDBMHEIGHT__
				}else {

				}				
			}
		} 
	}//end for

	delete [] distanceIndex0;
	delete [] distanceIndex1;

	
#ifdef CHECK_LEMA1
	// Distribute distance en DCmatrix of node0
	for ( i = 1; i < cluster[0].size(); i++) {
		for (j = 0; j < i; j++) { 	
			idx0 = cluster[0][i];
			idx1 = cluster[0][j];
			(*node0)(i, j) = DMat[idx0][idx1];
		}			
	}

	// Distribute distance en DCmatrix of node1
	for ( i = 1; i < cluster[1].size(); i++) {
		for (j = 0; j < i; j++) { 	
			idx0 = cluster[1][i];
			idx1 = cluster[1][j];
			(*node1)(i, j) = DMat[idx0][idx1];
		}			
	}
#endif
	
	// Representatives

	promo[0].Rep = BuyObject(GetRepresentativeIndex(0));
	promo[0].Radius = node0->GetMinimumRadius();
	promo[0].RootID = node0->GetPageID();
	promo[0].NObjects = node0->GetTotalObjectCount();


	promo[1].Rep = BuyObject(GetRepresentativeIndex(1));
	promo[1].Radius = node1->GetMinimumRadius();
	promo[1].RootID = node1->GetPageID();
	promo[1].NObjects = node1->GetTotalObjectCount();
}//end stDBMLogicNode::Distribute


template <class ObjectType, class EvaluatorType>
void stMStarLogicNode<ObjectType, EvaluatorType>::TestDistribution(
         tDBMMemNode * node0, tDBMMemNode * node1,
         EvaluatorType * metricEvaluator){
   int idx, i;
   int idx0, idx1;
   int currObj;
   stDistanceIndex * distanceIndex0, * distanceIndex1;
   stCount idxRep0, idxRep1;

   // Clean before use.
   node0->RemoveAll();
   node1->RemoveAll();

   // Get the index of representatives.
   idxRep0 = GetRepresentativeIndex(0);
   idxRep1 = GetRepresentativeIndex(1);

   // Get space to store.
   distanceIndex0 = new stDistanceIndex[this->Count];
   distanceIndex1 = new stDistanceIndex[this->Count];
   // Init Map
   for (i = 0; i < this->Count; i++){
      distanceIndex0[i].Index = i;
      distanceIndex0[i].Distance = DMat[i][idxRep0];
      distanceIndex1[i].Index = i;
      distanceIndex1[i].Distance = DMat[i][idxRep1];
      Entries[i].Mapped = false;
      Entries[i].Mine = true;
   }//end for
   // Sorting by distance...
   sort(distanceIndex0, distanceIndex0 + this->Count);
   sort(distanceIndex1, distanceIndex1 + this->Count);

   // Make one of then get the minimum occupation.
   idx0 = idx1 = 0;

   // Add at least this->MinOccupation objects to each node.
//   for (i = 0; i < 2; i++){
      // Find a candidate for node 1
      while (Entries[distanceIndex0[idx0].Index].Mapped){
         idx0++;
      }//end while
      // Add to node 1
      currObj = distanceIndex0[idx0].Index;
      Entries[currObj].Mapped = true;
      idx = node0->AddEntry(Entries[currObj].Object->GetSerializedSize(),
                            Entries[currObj].Object,
                            Entries[currObj].PageID);
      node0->SetEntry(idx, distanceIndex0[idx0].Distance
                    #ifdef __stDBMNENTRIES__
                       , Entries[currObj].NEntries
                    #endif //__stDBMNENTRIES__
                       , Entries[currObj].Radius
                    #ifdef __stDBMHEIGHT__
                       , Entries[currObj].Height
                    #endif //__stDBMHEIGHT__
                    );

      // Find a candidate for node 2
      while (Entries[distanceIndex1[idx1].Index].Mapped){
         idx1++;
      }//end while
      // Add to node 2
      currObj = distanceIndex1[idx1].Index;
      Entries[currObj].Mapped = true;
      idx = node1->AddEntry(Entries[currObj].Object->GetSerializedSize(),
                            Entries[currObj].Object,
                            Entries[currObj].PageID);
      node1->SetEntry(idx, distanceIndex1[idx1].Distance
                    #ifdef __stDBMNENTRIES__
                       , Entries[currObj].NEntries
                    #endif //__stDBMNENTRIES__
                       , Entries[currObj].Radius
                    #ifdef __stDBMHEIGHT__
                       , Entries[currObj].Height
                    #endif //__stDBMHEIGHT__
                    );
//   }//end for

   // Distribute the others.
   for (i = 0; i < this->Count; i++){
      // If this entry was not mapped.
      if (Entries[i].Mapped == false){
         // Set this entry to mapped.
         Entries[i].Mapped = true;
         // Where I will put it? In node 1 or 2?
         if (DMat[i][idxRep0] < DMat[i][idxRep1]){
            // This new entry has a distance to node 1 lesser than to node 2.
            // Try to put on node 1 first
            idx = node0->AddEntry(Entries[i].Object->GetSerializedSize(),
                                  Entries[i].Object,
                                  Entries[i].PageID);
            if (idx >= 0){
               node0->SetEntry(idx, DMat[i][idxRep0]
                             #ifdef __stDBMNENTRIES__
                                , Entries[i].NEntries
                             #endif //__stDBMNENTRIES__
                                , Entries[i].Radius
                             #ifdef __stDBMHEIGHT__
                                , Entries[i].Height
                             #endif //__stDBMHEIGHT__
                             );
            }else {
               // Let's put it in the node 2 since it doesn't fit in the node 1
               idx = node1->AddEntry(Entries[i].Object->GetSerializedSize(),
                                     Entries[i].Object,
                                     Entries[i].PageID);
               node1->SetEntry(idx, DMat[i][idxRep1]
                             #ifdef __stDBMNENTRIES__
                                , Entries[i].NEntries
                             #endif //__stDBMNENTRIES__
                                , Entries[i].Radius
                             #ifdef __stDBMHEIGHT__
                                , Entries[i].Height
                             #endif //__stDBMHEIGHT__
                             );
            }//end if
         }else{
            // Try to put on node 2 first
            idx = node1->AddEntry(Entries[i].Object->GetSerializedSize(),
                                  Entries[i].Object,
                                  Entries[i].PageID);
            if (idx >= 0){
               node1->SetEntry(idx, DMat[i][idxRep1]
                             #ifdef __stDBMNENTRIES__
                                , Entries[i].NEntries
                             #endif //__stDBMNENTRIES__
                                , Entries[i].Radius
                             #ifdef __stDBMHEIGHT__
                                , Entries[i].Height
                             #endif //__stDBMHEIGHT__
                             );
            }else {
               // Let's put it in the node 1 since it doesn't fit in the node 2
               idx = node0->AddEntry(Entries[i].Object->GetSerializedSize(),
                                     Entries[i].Object,
                                     Entries[i].PageID);
               node0->SetEntry(idx, DMat[i][idxRep0]
                             #ifdef __stDBMNENTRIES__
                                , Entries[i].NEntries
                             #endif //__stDBMNENTRIES__
                                , Entries[i].Radius
                             #ifdef __stDBMHEIGHT__
                                , Entries[i].Height
                             #endif //__stDBMHEIGHT__
                             );
            }//end if
         }//end if
      }//end if
   }//end for

   // Clean home before go away...
   delete[] distanceIndex0;
   delete[] distanceIndex1;

}//end stDBMLogicNode::TestDistribution


#endif //__stMStarLogicNode__


