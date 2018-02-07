// stRLogicNode.h: interface for the stRLogicNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRLOGICNODE_H__A740EE29_0F36_4F34_83F7_9EE82A938BA1__INCLUDED_)
#define AFX_STRLOGICNODE_H__A740EE29_0F36_4F34_83F7_9EE82A938BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stRTree.h"

#include <arboretum/stTypes.h>
#include <arboretum/stUtil.h>
#include <arboretum/stCommon.h>
#include "stSubTreeInfo.h"


template<class ObjectType>
class stRLogicNode  
{
    typedef stSubTreeInfo<ObjectType> tSubTreeInfo;
        
public:
	stRLogicNode(stSize n);
	virtual ~stRLogicNode();
	void SetMinOccupation(int occup);
	int  AddEntry(ObjectType* obj, stSize NEntries, stPageID pageID);
	void AddNode(stRNode* node);
	void Distribute(stRNode* node0, stRNode* node1, tSubTreeInfo* promo);
	stSize GetNumberOfEntries() {
		return this->Occupation;
	}

private:

	int		SelecPickNext(stMBR*  mbr0, stMBR*  mbr1);
	void	SelectPickSeeds(int& pos0, int& pos1);

private:
	struct stLogicEntry {
		ObjectType* Object;
		stSize		NEntries;
		stPageID	PageID;		
		bool		Mine;
	};
	stLogicEntry* Entries;
	stCount		  Occupation;
	stSize		  MaxNumberOfEntries;
	float		  MinOccupation;
};	


template<class ObjectType>
stRLogicNode<ObjectType>::stRLogicNode(stSize n){

	MaxNumberOfEntries = n;
	Entries = new stLogicEntry[MaxNumberOfEntries];
	Occupation = 0;
}

template<class ObjectType>
stRLogicNode<ObjectType>::~stRLogicNode()
{
	int idx;
	for (idx = 0; idx < this->GetNumberOfEntries(); idx++) {
		if( Entries[idx].Mine )
			delete Entries[idx].Object;
	}
	delete [] Entries;
}

template<class ObjectType>
void stRLogicNode<ObjectType>::SetMinOccupation(int occup)
{
	MinOccupation = occup;
}

template<class ObjectType>
void stRLogicNode<ObjectType>::AddNode(stRNode* node)
{
	int idx;
	for (idx = 0; idx < node->GetNumberOfEntries(); idx++) {
		ObjectType* tmpObj = new ObjectType;
		tmpObj->Unserialize(node->GetObject(idx), node->GetObjectSize(idx));
		this->AddEntry(tmpObj, node->GetNEntries(idx), node->GetEntry(idx).PageID);
	}
}

template<class ObjectType>
int  stRLogicNode<ObjectType>::AddEntry(ObjectType* obj, stSize NEntries, stPageID pageID)
{
	this->Entries[Occupation].Mine = true;
	this->Entries[Occupation].Object = obj;
	this->Entries[Occupation].PageID = pageID;
	this->Entries[Occupation].NEntries = NEntries;
	this->Occupation++;
	return Occupation - 1;
}
	

template<class ObjectType>
void stRLogicNode<ObjectType>::Distribute(stRNode* node0, stRNode* node1, tSubTreeInfo* promo)
{
	stRLogicNode* nodeLogic0,* nodeLogic1;
	int idx, i, idxSelect, insertIdx, pos0, pos1;
	int numberOfEntriesAdded;
	stDistance IR0, IR1;
	numberOfEntriesAdded = 0;
	nodeLogic0 = new stRLogicNode(this->GetNumberOfEntries());
	nodeLogic1 = new stRLogicNode(this->GetNumberOfEntries());

#ifdef __stDEBUG__ 	 
	for (idx = 0; idx < this->GetNumberOfEntries(); idx++) {
		Entries[idx].Object->Print(std::cout);
	}
#endif

	pos0 = pos1 = -1;
	this->SelectPickSeeds(pos0, pos1);
	//std::cout << "pos0: " << pos0 << "\t" << "pos1: " << pos1 << "\n";
	this->Entries[pos0].Mine = false;
	this->Entries[pos1].Mine = false;
	
	nodeLogic0->AddEntry(this->Entries[pos0].Object, this->Entries[pos0].NEntries, this->Entries[pos0].PageID);
	nodeLogic1->AddEntry(this->Entries[pos1].Object, this->Entries[pos1].NEntries, this->Entries[pos1].PageID);
	numberOfEntriesAdded = 2;
	while(numberOfEntriesAdded != this->GetNumberOfEntries()) {
		
		// find mbr of each group.
		stMBR* mbr0 = nodeLogic0->Entries[0].Object;
		for (i = 1; i < nodeLogic0->GetNumberOfEntries(); i++) {
		    mbr0 = mbr0->GetUnionMBR(nodeLogic0->Entries[i].Object);
		}
		stMBR* mbr1 = nodeLogic1->Entries[0].Object;
		for (i = 1; i < nodeLogic1->GetNumberOfEntries(); i++) {
		    mbr1 = mbr1->GetUnionMBR(nodeLogic1->Entries[i].Object);
		}
		idxSelect = this->SelecPickNext(mbr0, mbr1);
	 
#ifdef __stDEBUG__
		std::cout << "idxSelect: " << idxSelect << "\n";
#endif
		stMBR* a = mbr0->GetUnionMBR( Entries[idxSelect].Object );
		IR0 = a->GetArea() - mbr0->GetArea();
		stMBR* b = mbr1->GetUnionMBR( Entries[idxSelect].Object );
		IR1 = b->GetArea() - mbr1->GetArea();
		
		if( IR0 < IR1 ) {
			nodeLogic0->AddEntry(this->Entries[idxSelect].Object, this->Entries[idxSelect].NEntries, this->Entries[idxSelect].PageID);
		}
		else {
			nodeLogic1->AddEntry(this->Entries[idxSelect].Object, this->Entries[idxSelect].NEntries, this->Entries[idxSelect].PageID);
		}
		
		this->Entries[idxSelect].Mine = false;	//????
		numberOfEntriesAdded++;
	}
	
	for (idx = 0; idx < nodeLogic0->GetNumberOfEntries() ; idx++) {
		insertIdx = node0->AddEntry(nodeLogic0->Entries[idx].Object->GetSerializedSize(),
									nodeLogic0->Entries[idx].Object->Serialize(),
									nodeLogic0->Entries[idx].PageID);

		node0->SetNENtries(insertIdx, nodeLogic0->Entries[idx].NEntries);
	}
	for (idx = 0; idx < nodeLogic1->GetNumberOfEntries() ; idx++) {
		insertIdx = node1->AddEntry(nodeLogic1->Entries[idx].Object->GetSerializedSize(),
									nodeLogic1->Entries[idx].Object->Serialize(),
									nodeLogic1->Entries[idx].PageID);

		node1->SetNENtries(insertIdx, nodeLogic1->Entries[idx].NEntries);
	}

	stMBR* mbr0 = (stMBR*)nodeLogic0->Entries[0].Object->Clone();
	for (i = 1; i < nodeLogic0->GetNumberOfEntries(); i++) {
		mbr0 = mbr0->GetUnionMBR(nodeLogic0->Entries[i].Object);
	}
	stMBR* mbr1 = (stMBR*)nodeLogic1->Entries[0].Object->Clone();
	for (i = 1; i < nodeLogic1->GetNumberOfEntries(); i++) {
		mbr1 = mbr1->GetUnionMBR(nodeLogic1->Entries[i].Object);
	}
	promo[0].RootID = node0->GetPageID();
	promo[0].Rep = (ObjectType*)mbr0;
	promo[0].NObjects = node0->GetTotalObjectCount();

	promo[1].RootID = node1->GetPageID();
	promo[1].Rep = (ObjectType*)mbr1;
	promo[1].NObjects = node1->GetTotalObjectCount();
}



template<class ObjectType>
void stRLogicNode<ObjectType>::SelectPickSeeds(int& pos0, int& pos1)
{
	stDistance  d, 
				max = -1.00;
	int i, j;
	for(i = 1; i < this->GetNumberOfEntries() ;i++ ) {
		for (j = 0; j < i; j++) {
			stMBR* mbr = Entries[i].Object->GetUnionMBR(Entries[j].Object);
			d = fabs(mbr->GetArea() - Entries[i].Object->GetArea() - Entries[j].Object->GetArea());
			if( d > max ){
				max = d;
				pos0 = i;
				pos1 = j;
			}
		}
	}
	assert(pos0 >= 0 && pos1 >= 0);
}

template<class ObjectType>
int stRLogicNode<ObjectType>::SelecPickNext(stMBR*  mbr0, stMBR*  mbr1)
{
	stDistance d0, d1, max = -1.00;
	int idx, ret = -1;
	for (idx = 0; idx < this->GetNumberOfEntries(); idx++){
		if(Entries[idx].Mine == false ) continue;

		stMBR* a = mbr0->GetUnionMBR( Entries[idx].Object );
		d0 = a->GetArea() - mbr0->GetArea();
		
		stMBR* b = mbr0->GetUnionMBR( Entries[idx].Object );
		d1 = b->GetArea() - mbr1->GetArea();
		
		if( fabs(d0 - d1) > max) {
			max = fabs(d0 - d1);
			ret = idx;
		}
		delete a;
		delete b;
	}
	
	//if (mask[i] != -1) {
	//HyperCube a = mbr1.getUnionMbb(data[i]);
	//d1 = a.getArea() - mbr1.getArea();
	assert(ret >= 0);		
	return ret;
}

#endif // !defined(AFX_STRLOGICNODE_H__A740EE29_0F36_4F34_83F7_9EE82A938BA1__INCLUDED_)
