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
			ptr = index(ptr + i);
			data_[ptr] = t;
			increaseItemAmount();
		}
		std::cout << first_ << " " << last_ << " " << ptr << std::endl;
	}

	void addFirst(T t)
	{
		//addItem(t, -1);
		if (itemsAmount_ == 0)
		{
			data_[first_] = t;
			increaseItemAmount();
		}
		else
		{
			first_ = index(first_ - 1);
			data_[first_] = t;
			increaseItemAmount();
		}
		std::cout << first_ << " " << last_ << std::endl;
	}

	void addLast(T t)
	{
		//addItem(t, 1);
		if (itemsAmount_ == 0)
		{
			data_[last_] = t;
			increaseItemAmount();
		}
		else
		{
			last_ = index(last_ + 1);
			data_[last_] = t;
			increaseItemAmount();
		}
		std::cout << first_ << " " << last_ << std::endl;
	}

	void delFirst()
	{
		data_[first_] = 0;
		first_ = index(first_ + 1);
		decreaseItemAmount();
	}

	void delLast()
	{
		data_[last_] = 0;
		last_ = index(last_ - 1);
		decreaseItemAmount();
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

	void changeCapacity(int newCapacity)
	{
		int itemsFit = (itemsAmount_ < newCapacity) ? itemsAmount_ : newCapacity;
		T *buf = new T[newCapacity];
		for (int i = 0; i < itemsFit; i++)
		{
			buf[i] = data_[index(first_ + i)];
		}
		itemsAmount_ = itemsFit;
		data_ = buf;
		first_ = 0;
		last_ = itemsAmount_ - 1;
		capacity_ = newCapacity;
	}

	void show() const
	{
		for (int i = 0; i < capacity_; i++)
			std::cout << data_[i] << " ";
		std::cout << std::endl;
	}
};
