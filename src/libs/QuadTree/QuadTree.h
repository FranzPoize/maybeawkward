#ifndef QuadTree_h__
#define QuadTree_h__

#define QUADSUBTREE 4

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
class QuadTree
{
public:
	QuadTree(int aDepth, BoundingBox aBox);
	void insertElement(T *element);
	void clear();
	std::vector<T*> searchNeighbors();

protected:
	void split();
	bool doesItFit(BoundingBox box);

private:
	typedef std::list<T_Element *> SubTreeContainer
	typedef SubTreeContainer::iterator SubTreeIterator;

	int mDepth;
	T_BoundingBox mBox;
	SubTreeContainer mDirectElements;

	std::unique_ptr<QuadTree> mSubTrees[QUADSUBTREE];

	bool mLevelFull;

	//std::unique_ptr<QuadTree<T> > mNorthWest;
	//std::unique_ptr<QuadTree<T> > mNorthEast;
	//std::unique_ptr<QuadTree<T> > mSouthWest;
	//std::unique_ptr<QuadTree<T> > mSouthEast;
};


template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::QuadTree(int aDepth, T_BoundingBox aBox):
	mDepth(aDepth),
	mBox(aBox)
{
	split();
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
		SubTreeContainer::elemIt = mDirectElements.end();
		do
		{
			--elemIt;
			insertElement(elemIt);
			elemIt = mDirectElements.erase(elemIt);
		}
		while(elemIt != mDirectElements.begin())

		insertElement(aElement)
	}
	else
	{
		for(size_t subTreeId = 0;
			subTreeId != QUADSUBTREE;
			++subTreeId)
		{
			if(mSubTrees[subTreeId]->doesItFit(aElement.getBB()))
			{
				mSubTrees[subTreeId]->insertElement(aElement);
				return;
			}
		}

		mDirectElements.push_back(aElement);
	}

}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::split()
{
	for(size_t subTreeId = 0;
		subTreeId != QUADSUBTREE;
		++subTreeId)
	{
		mSubTrees[subTreeId].reset(new QuadTree(mDepth+1, mBox.getQuadrant(subTreeId)))
	}
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::doesItFit(const T_BoundingBox &aBbox)
{
	return mBox.contains(aBbox);
}

template <class T_Element, class T_BoundingBox,
	int MAX_OBJECTS, int MAX_LEVELS>
void QuadTree<T_Element, T_BoundingBox, MAX_OBJECTS, MAX_LEVELS>::clear()
{
	mDirectElements.clear();

	for(size_t subTreeId = 0;
		subTreeId != QUADSUBTREE;
		++subTreeId)
	{
		mSubTrees[subTreeId]->clear();
	}
}

#endif // QuadTree_h__



