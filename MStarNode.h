#ifndef  _stMStarNode_h_
#define  _stMStarNode_h_

#include "arboretum/stPage.h"
#include "arboretum/stTypes.h"
#include "arboretum/stException.h"

#include <cassert>
#include <iostream>
#include <iomanip>

#define ENTRY_SIZE		sizeof(stMStarNode::Entry)
#define NODE_HEAD_SIZE	sizeof(stMStarNode::MStarNodeHeader)
#define SIZE_MATRIX(n)	((n)*((n)-1)/2)

//#define OBJECT_SIZE ((sizeof(char [40])) + 2*sizeof(double))
//#define OBJECT_SIZE ((sizeof(char [40])) + 2*sizeof(double))
//#define OBJECT_SIZE (sizeof(char [32]))
#define TDIMENSION 3
#define OBJECT_SIZE (TDIMENSION*sizeof(float) + sizeof(char)*32)
//#define OBJECT_SIZE (sizeof(char [32]))
//#define OBJECT_SIZE (sizeof(char [32]))

class stMStarNode{	
public:
	struct MStarNodeHeader {
		stSize		Occupation;
		stSize		Order;
		size_t		ObjSize;
	};
	struct Entry {
		stPageID	PageID;	
		stDistance	Distance;
		stDistance	Radius;
		stSize		NEntries;
	};
	
public:
	stMStarNode(stPage* page, const size_t create = 0) : m_Mtx(NULL){	
		m_Page	 = page;
		m_Header = (MStarNodeHeader*)(m_Page->GetData());
		m_Entries  = (Entry* )(m_Page->GetData() + sizeof(MStarNodeHeader));
		
		//check if create if the value of the order tree
		if(create != 0) {
			m_Page->Clear();
			m_Header->Order = create;
			m_Header->ObjSize = OBJECT_SIZE;
		}//endif
		 
		//std::cout << "<*>posMtx: " << (int)(m_Page->GetData() + GetFirstPosObject() + (m_Header->Order+1)*OBJECT_SIZE) << "\t"
		//			<< "id: " <<  page->GetPageID() << std::endl;
		(stDistance *)m_Mtx = (stDistance *)(m_Page->GetData() + GetFirstPosObject() + (m_Header->Order+1)*OBJECT_SIZE);	
		if(create != 0) {
			ClearMatrix();			
		}
	}
	
	int AddEntry(size_t size, const stByte * obj, stPageID subTree) {
		m_Header->ObjSize = size;
		memcpy(	m_Page->GetData() + GetFirstPosObject() + size*m_Header->Occupation,
				obj,
				size );
//std::cout << (m_Page->GetData() + GetFirstPosObject() + size*m_Header->Occupation + size) - (m_Page->GetData() + GetMatrixPos()) << std::endl;

assert((m_Page->GetData() + GetFirstPosObject() + size*m_Header->Occupation + size) <= (m_Page->GetData() + GetMatrixPos()) );
		
		m_Entries[m_Header->Occupation].PageID = subTree;
		++m_Header->Occupation;
		return m_Header->Occupation - 1;
	}
	
	int SetEntry(const stByte * obj, size_t size, stPageID subTree, size_t idx) {
		memcpy(	m_Page->GetData() + GetFirstPosObject() + size*idx,
				obj,
				size);
		m_Entries[idx].PageID = subTree;
		return idx;
	}

	const stByte* GetObject(size_t pos) {
		assert( pos <= m_Header->Occupation );
		return (stByte *)(m_Page->GetData() + GetFirstPosObject() + pos*m_Header->ObjSize);
	}
	
	stSize GetObjectSize(size_t pos) {
		assert( pos <= m_Header->Occupation );
		return m_Header->ObjSize;
	}

	Entry& GetEntry(size_t pos) {
		assert(pos <= m_Header->Order);
		return m_Entries[pos];
	}

	size_t FindRemote(){
		size_t ret = 1;
		stDistance max = 0.0f;
		for (size_t i = 0; i < GetNumberOfEntries(); i++) {
			if ( m_Entries[i].Distance > max ){
				max  = m_Entries[i].Distance;
				ret = i; 
			}
		}
		return ret;
	}
	int GetFarthestObject() {
		size_t ret = 1;
		stDistance max = 0.0f;
		for (size_t i = 0; i < GetNumberOfEntries(); i++) {
			if ( m_Entries[i].Distance > max ){
				max  = m_Entries[i].Distance;
				ret = i; 
			}
		}
		return ret;
	}

	int FindRemoteTo(int idxRep) {
		int ret = -1;
		stDistance max = 0.0f;
		for (size_t i = 0; i < GetNumberOfEntries(); i++) {
			if ( m_Entries[i].Distance > max ){
				max  = m_Entries[i].Distance;
				ret = i; 
			}
		}
		return ret;
	}

	stCount		GetNEntries(stCount idx);
	void		SetNEntries(stCount idx, stCount NEntries);
	stDistance	GetRadius(stCount idx);
	void		SetRadius(stCount idx, stDistance radius);

	/**
	* Returns the minimum radius of this node.
	*/
	stDistance GetMinimumRadius();

	/**
	* Returns the total number of objects in the subtree.
	*/
	stCount GetTotalObjectCount();
	
	/**
	* Returns the number of free objects in this node.
	*/
	stCount GetNumberOfFreeObjects();
	
	void RemoveEntry(stCount idx);

	void RemoveAll()
	{
		#ifdef __stDEBUG__
			m_Page->Clear();
		#else
    		this->m_Header->Occupation = 0;
		#endif //__stDEBUG__
		this->Reset();
	}

	int			GetRepresentativeIndex();

	bool		IsSubTree(size_t pos) const		{ return m_Entries[pos].PageID != 0;	}
	stPageID	GetPageID()  const				{ return m_Page->GetPageID();		}
	stPage*		GetPage()  const				{ return m_Page;		}
	
	bool		IsOverflow() const				{ return m_Header->Order < m_Header->Occupation; }
	size_t		GetNumberOfEntries() const		{ return m_Header->Occupation;}
	
	void PrintMatrix(){
		using std::setw;
		std::cout.precision(2);
        int i;
		std::cout << "\n";
		for (i=0; i<m_Header->Occupation; i++) {
			std::cout << m_Entries[i].Distance << ", "; 
		}
		std::cout << "\n\n" << "posMtx: " << (int)((double*)m_Mtx) << std::endl;
		for (i=0; i<m_Header->Order+1;i++) {
			for (int j=0; j<m_Header->Order+1;j++){
				if( at(i, j) >= 0.0)
					std::cout << setw(3) << at( i, j ) << ", ";
				else
					std::cout << setw(3) << "-" << ", ";

			}
			std::cout << "\n";
		}
		
	}
	
	void	Reset()	{ 
		m_Header->Occupation = 0;
		ClearMatrix();
	}
  
	stDistance at(size_t i, size_t j) const {	//< show value	: R-value
		if( i > (this->m_Header->Order+1) || j > (this->m_Header->Order+1) )
			return -1.0;
		return i == j ? 0.0f : j < i ?  m_Mtx[i * (i - 1) / 2 + j] : m_Mtx[j * (j - 1) / 2 + i];
	}
	stDistance operator()(size_t i, size_t j) const {	//< show value	: R-value
		return i == j ? 0.0f : j < i ?  m_Mtx[i * (i - 1) / 2 + j] : m_Mtx[j * (j - 1) / 2 + i];
	}
	stDistance &operator()(size_t i, size_t j) {  //< assignment	: L-value
		return j < i ?  m_Mtx[i * (i - 1) / 2 + j] : m_Mtx[j * (j - 1) / 2 + i];			
	}
	void ClearMatrix(){
		for (size_t i=0; i < SIZE_MATRIX(m_Header->Order+1); i++) {
			m_Mtx[i] = -1.0f;
		}
		//PrintMatrix();
	}
private:


	size_t		   GetMatrixPos() const   { return GetFirstPosObject() + (m_Header->Order+1)*OBJECT_SIZE;			}
	size_t		   GetFirstPosObject() const { return sizeof(MStarNodeHeader) + (m_Header->Order + 1)*sizeof(Entry);}
	static size_t  GetHeaderSize() { return sizeof(MStarNodeHeader); }
	static size_t  GetEntrySize() { return sizeof(Entry); }
	
private:
	stPage*				m_Page;
	stDistance * const	m_Mtx;
	MStarNodeHeader*	m_Header;			
	Entry*				m_Entries;
};


#endif //__MStarNode_h_
