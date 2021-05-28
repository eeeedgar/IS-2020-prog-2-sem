#include <iostream>
#include <iterator>


template <class T>
class CircularBuffer;

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
 private:
	Iterator(T* p)
		: p_(p)
	{
	};
	T* p_;
 public:
	friend class CircularBuffer<T>;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

	Iterator(const Iterator& it)
		: p_(it.p_)
	{
	}

	bool operator!=(Iterator const& other) const
	{
		return p_ != other.p_;
	}

	typename Iterator::reference operator=(Iterator const& other)
	{
		*p_ = *other.p_;
		return *p_;
	}

	bool operator==(Iterator const& other) const
	{
		return !(*this != other);
	}

	typename Iterator::reference& operator*() const
	{
		return *p_;
	}

	typename Iterator::reference& operator[](unsigned int n) const
	{
		return *(p_ + n);
	}

	Iterator& operator+=(int x)
	{
		p_ += x;
		return *this;
	}

	Iterator& operator-=(int x)
	{
		*this += x * (-1);
		return *this;
	}

	Iterator operator-(int x) const
	{
		return Iterator(p_ - x);
	}

	Iterator operator+(int x) const
	{
		return Iterator(p_ + x);
	}

	T operator-(Iterator x)
	{
		return (p_ - x.p_);
	}

	bool operator<(const Iterator& other) const
	{
		return other.p_ < this->p_;
	}

	bool operator>(const Iterator& other) const
	{
		return other.p_ > this->p_;
	}

	bool operator<=(const Iterator& other) const
	{
		return !(*this < other);
	}

	bool operator>=(const Iterator& other) const
	{
		return !(other < *this);
	}

	Iterator& operator++()
	{
		p_++;
		return *this;
	}

	Iterator& operator--()
	{
		p_--;
		return *this;
	}
};



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

	void addFirst(T t)
	{
		if (itemsAmount_ == 0)
		{
			data_[first_] = t;
			increaseItemAmount();
		}
		else
		{
			first_ = index(first_ - 1);
			if (first_ == last_)
				last_ = index(last_ - 1);
			data_[first_] = t;
			increaseItemAmount();
		}
	}

	void addLast(T t)
	{
		if (itemsAmount_ == 0)
		{
			data_[last_] = t;
			increaseItemAmount();
		}
		else
		{
			last_ = index(last_ + 1);
			if (last_ == first_)
				first_ = index(first_ + 1);
			data_[last_] = t;
			increaseItemAmount();
		}
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

	T operator[](int i) const
	{
		if (i < itemsAmount_ and i >= 0)
			return data_[index(first_ + i)];
		else
		{
			std::string error = "Element ";
			error += std::to_string(i);
			error += " doesn't exist";
			throw std::range_error(error);
		}
	}

	T &operator[](int i)
	{
		if (i < itemsAmount_ and i >= 0)
			return data_[index(first_ + i)];
		else
		{
			std::string error = "Out of Range. Index: ";
			error += std::to_string(i);
			error += ". Buffer capacity is ";
			error += std::to_string(itemsAmount_);
			throw std::out_of_range(error);
		}
	}

	friend class Iterator<T>;
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	iterator begin() const
	{
		return iterator(data_ + first_);
	}

	iterator end() const
	{
		return iterator(data_ + itemsAmount_ + 1);
	}

};
