#include <iostream>
#include <vector>

template <class T>
class CircularBuffer
{
 private:
	T *data_;
	int capacity_;
	int first_;
	int last_;
	int itemsAmount_;
 public:
	explicit CircularBuffer(int capacity)
		: capacity_(capacity)
		, first_(0)
		, last_(0)
	{
		data_ = new T[capacity];
	}

	void addItem(T t, int i)	//	-1 - first, 1 - last
	{
		int ptr = first_;
		if (i == 1)
			ptr = last_;

		if (itemsAmount_ == 0)
		{
			data_[ptr] = t;
			increaseItemAmount();
		}
		else
		{
			first_ = index(ptr + i);
			data_[first_] = t;
			increaseItemAmount();
		}
	}

	void addFirst(T t)
	{
		addItem(t, -1);
	}

	void addLast(T t)
	{
		addItem(t, 1);
	}

	T &first() const
	{
		return data_[first_];
	}

	T &last() const
	{
		return data_[last_];
	}

	int index(int i) const
	{
		if (i >= capacity_)
			return (i) % capacity_;
		return i;
	}

	void increaseItemAmount()
	{
		if (itemsAmount_ < capacity_)
			itemsAmount_++;
	}

	void decreaseItemAmount()
	{
		if (itemsAmount_ > 0)
			itemsAmount_--;
	}
};
