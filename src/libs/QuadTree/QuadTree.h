#ifndef QuadTree_h__
#define QuadTree_h__

#include <list>
#include <vector>
#define QUADSUBTREE 4

namespace BHQT
{
template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
class QuadTree
{
public:
	//typedef std::list<T_Element *> ElementsContainer;
	typedef std::vector<T_Element *> ElementsContainer;
	//typedef SubTreeContainer::iterator SubTreeIterator;


	QuadTree(int aDepth, T_BoundingBox aBox,QuadTree *aParent = 0);
	void insertElement(T_Element *element);
	void clear();
	ElementsContainer searchNeighbors(const T_Element &element);

protected:
	void addChildrenElements(ElementsContainer &aContainer);
	void addParentsDirectElements(ElementsContainer &aContainer);
	void split();

	void concreteInsert(T_Element *aElement);
	bool doesItFit(const T_BoundingBox& box);

private:

	int mDepth;
	T_BoundingBox mBox;
	ElementsContainer mDirectElements;

	std::unique_ptr<QuadTree> mSubTrees[QUADSUBTREE];
	QuadTree* mParent;

	bool mLevelFull;

	//std::unique_ptr<QuadTree<T> > mNorthWest;
	//std::unique_ptr<QuadTree<T> > mNorthEast;
	//std::unique_ptr<QuadTree<T> > mSouthWest;
	//std::unique_ptr<QuadTree<T> > mSouthEast;
};


template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::QuadTree(int aDepth, T_BoundingBox aBox, QuadTree *aParent):
	mDepth(aDepth),
	mBox(aBox),
	mParent(aParent)
{
	if(MAX_LEVELS != aDepth)
	{
		split();
	}
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::insertElement(T_Element *aElement)
{
	if (!mLevelFull
		&&mDepth < MAX_LEVELS
		&& mDirectElements.size() >= MAX_OBJECTS)
	{
		mLevelFull = true;
		//ElementsContainer::iterator elemIt = mDirectElements.end();
		//do
		//{
		//	--elemIt;
		//	insertElement(*elemIt);
		//	elemIt = mDirectElements.erase(elemIt);
		//}
		//while(elemIt != mDirectElements.begin());

		insertElement(aElement);
	}
	else
	{
		 if(mDepth != MAX_LEVELS)	
		 {
			for(size_t subTreeId = 0;
				subTreeId != QUADSUBTREE;
				++subTreeId)
			{
				if(mSubTrees[subTreeId]->doesItFit(aElement->getBoundingBox()))
				{
					mSubTrees[subTreeId]->insertElement(aElement);
					return;
				}
			}
		 }

		concreteInsert(aElement);
	}
	

}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::concreteInsert(T_Element *aElement)
{
	mDirectElements.push_back(aElement);
	aElement->setQuadTree(this);
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::split()
{
	for(size_t subTreeId = 0;
		subTreeId != QUADSUBTREE;
		++subTreeId)
	{
		mSubTrees[subTreeId].reset(new QuadTree(mDepth+1, mBox.getQuadrant(subTreeId),this));
	}
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
bool QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::doesItFit(const T_BoundingBox &aBbox)
{
	return mBox.contains(aBbox);
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::clear()
{
	mDirectElements.clear();

	if(!mSubTrees[0])
	{
		return;
	}
	for(size_t subTreeId = 0;
		subTreeId != QUADSUBTREE;
		++subTreeId)
	{
		mSubTrees[subTreeId]->clear();
	}
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
typename QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::ElementsContainer
	QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::searchNeighbors(const T_Element &element)
{
	ElementsContainer result;
	
	addParentsDirectElements(result);
	addChildrenElements(result);

	return result;
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::addParentsDirectElements(ElementsContainer &aContainer)
{
	aContainer.insert(aContainer.end(), mDirectElements.begin(), mDirectElements.end());	
	if(mParent)
	{
		mParent->addParentsDirectElements(aContainer);
	}
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::addChildrenElements(ElementsContainer &aContainer)
{
	if(!mSubTrees[0])
	{
		return;
	}
	for(int subTreeId = 0; subTreeId < QUADSUBTREE;++subTreeId)
	{
		QuadTree *childQuad = mSubTrees[subTreeId].get();
		aContainer.insert(aContainer.end(), childQuad->mDirectElements.begin(), childQuad->mDirectElements.end());

		childQuad->addChildrenElements(aContainer);
	}
}


}
#endif // QuadTree_h__



