#ifndef __stMStarSplitter__
#define  __stMStarSplitter__

#include "stMStarLogicNode.h"

	#include <iomanip>

template<class ObjectType, class EvaluatorType>
class stMStarTree;

//=============================================================================
// Class template stSlimMSTSpliter
//-----------------------------------------------------------------------------
/**
* This class template implements the SlimTree MST split algorithm.
*
* @version 1.0
* @author Alexander Ocsa 
*/
template <class ObjectType, class EvaluatorType>
class stMStarSplitter{
   public:
      typedef stMStarLogicNode < ObjectType, EvaluatorType > tLogicNode;
      typedef stMStarTree<ObjectType, EvaluatorType>::stSubtreeInfo  tSubtreeInfo;

	  stMStarSplitter(tLogicNode * node);

      ~stMStarSplitter();

      /**
      * Provides access to the logic node.
      */
      const tLogicNode * GetLogicNode(){
         return Node;
      }//end GetLogicNode

      /**
      * Distributes objects between 2 nodes.
      *
      * @param node0 The first node.
      * @param node1 The second node.
      * @param promo Representatives of node 0 and 1.
      * @param metricEvaluator The metric evaluator to be used to compute
      * distances.
      */
      stCount Distribute(stMStarNode * node0, stMStarNode * node1,
                         tSubtreeInfo * promo, EvaluatorType * metricEvaluator);

   private:

      /**
      * Distance matrix type.
      */
      typedef stGenericMatrix <stDistance> tDistanceMatrix;


      /**
      * The logic node to be used as source.
      */
      tLogicNode * Node;

      /**
      * The distance matrix.
      */
      tDistanceMatrix& DMat;

      /**
      * Total number of objects.
      */
      int N;

      stCount BuildDistanceMatrix(EvaluatorType * metricEvaluator);
      void PerformMST();
	  void Promote();
	  void CheckDistribution(stMStarNode* node, EvaluatorType * metricEvaluator);    
};//end stMStarSplitter


#include <vector>

//=============================================================================
// Class template stDBMMSTSpliter
//-----------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
stMStarSplitter<ObjectType, EvaluatorType>::stMStarSplitter(tLogicNode * node) 
	: DMat(node->DMat)
{

   this->Node = node;
   this->N = Node->GetNumberOfEntries();

   // Matrix
   //DMat.SetSize(N, N);
}//end stMStarSplitter::stMStarSplitter

//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
stMStarSplitter<ObjectType, EvaluatorType>::~stMStarSplitter(){

}//end stMStarSplitter::~stMStarSplitter

//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
stCount stMStarSplitter<ObjectType, EvaluatorType>::BuildDistanceMatrix(
      EvaluatorType * metricEvaluator){
   int i;
   int j;

   for (i = 0; i < N; i++){
      DMat[i][i] = 0;
      for (j = 0; j < i; j++){
         DMat[i][j] = metricEvaluator->GetDistance(Node->GetObject(i),
                                                   Node->GetObject(j));
         DMat[j][i] = DMat[i][j];
      }//end for
   }//end for
   return ((N - 1) * N) / 2;
}//end stMStarSplitter::BuildDistanceMatrix


//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
void stMStarSplitter<ObjectType, EvaluatorType>::PerformMST(){
   int i, j, k, l, cc, iBig, iBigOpposite, a, b, c;
   bool linksOk, flag;
   stDistance big;

   // Representatives
   //Node->SetRepresentative(FindCenter(Cluster0), FindCenter(Cluster1));
}//end stMStarSplitter::PerformMST
//------------------------------------------------------------------------------

template <class ObjectType, class EvaluatorType>
void stMStarSplitter<ObjectType, EvaluatorType>::Promote()
{
	//MinMax
	int i, j, k;
	int idxRep0, idxRep1;
	stDistance minimum = MAXDOUBLE;
	stDistance radius0(0.0f), radius1(0.0f);

	for (i = 1; i < N; i++) {
		for (j = 0; j < i; j++) {
			for (k = 0; k < N; k++) {
				if( DMat[i][k] < DMat[j][k] ) {
					if ( radius0 < DMat[i][k] ) {
						radius0 = DMat[i][k];
					}
				}
				else {
					if ( radius1 < DMat[j][k] ) {
						radius1 = DMat[j][k];
					}
				}
			}
			if (radius0 < radius1){
				radius0 = radius1;
			}

			if (radius0 < minimum) {
				minimum = radius0;
				idxRep0 = i;
				idxRep1 = j;
			}
		}
	}
	Node->SetRepresentative( idxRep0, idxRep1);
}

//------------------------------------------------------------------------------
template <class ObjectType, class EvaluatorType>
stCount stMStarSplitter<ObjectType, EvaluatorType>::Distribute(
            stMStarNode * node0, stMStarNode * node1,
            tSubtreeInfo * promo, EvaluatorType * metricEvaluator){
	
//	stCount distanceCount;
	int idx, idxInNode, i, j, idxRep0, idxRep1;
	std::vector<int> cluster[2];
	
	//distanceCount = BuildDistanceMatrix(metricEvaluator); //N*(N-1)/2;
	
	Promote();
	
	idxRep0 = Node->GetRepresentativeIndex(0);
	idxRep1 = Node->GetRepresentativeIndex(1);
	
	// Distribute the objects
	cluster[0].push_back(idxRep0);
	cluster[1].push_back(idxRep1);
	for (i = 0; i < Node->GetNumberOfEntries(); i++) {
		if ( ( i == idxRep0) || (i == idxRep1) ) continue;
		if (cluster[0].size() >= (N - 2) ) {
			cluster[1].push_back(i);
		}
		else if (cluster[1].size() >= (N - 2) ) {	// chekar esto.....
			cluster[0].push_back(i);
		}
		else if ( DMat[i][idxRep0] < DMat[i][idxRep1] ) {
			cluster[0].push_back(i);
		}
		else {
			cluster[1].push_back(i);
		}
	}

	// distribute the first cluster   
	for(i = 0; i < cluster[0].size(); i++) {
		idxInNode = cluster[0][i];
		idx = node0->AddEntry(Node->GetObject( idxInNode )->GetSerializedSize(),
							  Node->GetObject( idxInNode )->Serialize(),
							  Node->GetPageID( idxInNode ));
		if (idx >= 0) {
			/*if (idx == 0) {
				printf("idxInNode: %d -  idxRep0: %d\t", idxInNode, idxRep0);
				printf("dist: %f\n", (int)DMat[idxInNode][idxRep0]);
			}*/
			node0->GetEntry(idx).Distance = DMat[idxInNode][idxRep0];
			node0->SetRadius(idx, Node->GetRadius(idxInNode) );
			node0->SetNEntries(idx, Node->GetNEntries(idxInNode) );
			
			//(*node0)(idxInNode, idxRep0) = DMat[idxInNode][idxRep0]; 
		}
		else {
			// In the static version these case does not enter
		}
	}

	// distribute the second cluster	
	for(i = 0; i < cluster[1].size(); i++) {
		idxInNode = cluster[1][i];
		idx = node1->AddEntry(Node->GetObject( idxInNode )->GetSerializedSize(),
							  Node->GetObject( idxInNode )->Serialize(),
							  Node->GetPageID( idxInNode ));
		if (idx >= 0) {
			/*if (idx == 0) {
				printf("idxInNode: %d -  idxRep1: %d\t", idxInNode, idxRep1);
				printf("dist: %f\n", (int)DMat[idxInNode][idxRep1]);
			}*/
			node1->GetEntry(idx).Distance = DMat[idxInNode][idxRep1];
			node1->SetRadius(idx, Node->GetRadius(idxInNode) );
			node1->SetNEntries(idx, Node->GetNEntries(idxInNode) );

			//(*node1)(idxInNode, idxRep1) = DMat[idxInNode][idxRep1]; 
		}
		else {
			// In the static version these case does not enter
		}
	}
	int idx0, idx1;
	for ( i = 1; i < cluster[0].size(); i++) {
		for (j = 0; j < i; j++) { 	
			idx0 = cluster[0][i];
			idx1 = cluster[0][j];
			(*node0)(i, j) = DMat[idx0][idx1];
		}			
	}

	for ( i = 1; i < cluster[1].size(); i++) {
		for (j = 0; j < i; j++) { 	
			idx0 = cluster[1][i];
			idx1 = cluster[1][j];
			(*node1)(i, j) = DMat[idx0][idx1];
		}			
	}
	
	#ifdef __stDEBUB__
	CheckDistribution(node0, metricEvaluator);
	CheckDistribution(node1, metricEvaluator);
	#endif
	/*for ( i = 0; i < N; i++) {
		for (j = 0; j < N; j++) { 	
			cout << setw(3) << std::setprecision(2) << DMat[i][j] << " ";
		}
		printf("\n");		
	}*/

	//node0->GetEntry(idxRep0).Distance = 0.0f;
	//node1->GetEntry(idxRep1).Distance = 0.0f;

	// Representatives
	promo[0].Rep	  = Node->BuyObject(idxRep0);
	promo[0].Radius   = node0->GetMinimumRadius();
	promo[0].RootID   = node0->GetPageID();
    promo[0].NObjects = node0->GetTotalObjectCount();
   
	promo[1].Rep	  = Node->BuyObject(idxRep1);
	promo[1].Radius   = node1->GetMinimumRadius();
	promo[1].RootID   = node1->GetPageID();
	promo[1].NObjects = node1->GetTotalObjectCount();
   
//	assert(node0->GetRepresentativeIndex() >= 0);
//	assert(node1->GetRepresentativeIndex() >= 0);	
	
	/*node0->PrintMatrix();
	node1->PrintMatrix();
	cin.get();*/
	return 0;
}//end stMStarSplitter::Distribute



template <class ObjectType, class EvaluatorType>
void stMStarSplitter<ObjectType, EvaluatorType>::CheckDistribution(stMStarNode* node, EvaluatorType * metricEvaluator)
{
	int i, j, numberOfEntries;
	ObjectType *objI, *objJ;
	objI = new ObjectType;
	objJ = new ObjectType;

	numberOfEntries = node->GetNumberOfEntries();
	for (i = 0; i < numberOfEntries; i++) {
		for(j = 0; j < i; j++) {
			objI->Unserialize(node->GetObject(i), node->GetObjectSize(i));
			objJ->Unserialize(node->GetObject(j), node->GetObjectSize(j));
			if( node->at(i, j) != metricEvaluator->GetDistance(objI, objJ) ) {
				printf("nodeID =%d\n", node->GetPageID());
				printf("error_Splitter: distribution=> i=%d, j=%d\n", i, j);
				cin.get();
			}		
		}
	}
	delete objI;
	delete objJ;
}

#endif  // __stMStarSplitter__
