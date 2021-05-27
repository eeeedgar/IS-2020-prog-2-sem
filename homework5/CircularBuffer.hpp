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
			itemsAmount_++;
		}
		else
		{
			first_ = index(ptr + i);
			data_[first_] = t;
			itemsAmount_++;
		}
	}

	void addFirst(T t)
	{
		if (itemsAmount_ == 0)
		{
			data_[first_] = t;
			itemsAmount_++;
		}
		else
		{
			first_ = index(first_ - 1);
			data_[first_] = t;
			itemsAmount_++;
		}
	}

	void addLast(T t)
	{
		if (itemsAmount_ == 0)
		{
			data_[last_] = t;
			itemsAmount_++;
		}
		else
		{
			last_ = index(last_ + 1);
			data_[last_] = t;
			itemsAmount_++;
		}
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

	void addItem()
	{
		if (itemsAmount_ < capacity_)
			itemsAmount_++;
	}

	void deleteItem()
	{
		if (itemsAmount_ > 0)
			itemsAmount_--;
	}
};
