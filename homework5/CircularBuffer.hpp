#include <iterator>

template <typename T>
class CircularBuffer;

template <typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
 private:
	Iterator(T* p, int first, int capacity, int items)
		: data_(p), first_(first), capacity_(capacity), current_(items)
	{
	};
	T* data_;
	int first_;
	int capacity_;
	int current_;

 public:
	friend class CircularBuffer<T>;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

	Iterator(const Iterator& it)
		: data_(it.data_), first_(it.first_), capacity_(it.capacity_), current_(it.current_)
	{
	};

	Iterator& operator=(Iterator const& other)
	{
		data_ = other.data_;
		first_ = other.first_;
		capacity_ = other.capacity_;
		current_ = other.current_;
		return *this;
	};

	T& operator*() const
	{
		return data_[(first_ + current_) % capacity_];
	};

	T* operator->()
	{
		return &current_;
	};

	Iterator& operator+=(difference_type x)
	{
		current_ = current_ + x;
		return *this;
	};

	Iterator& operator-=(int x)
	{
		current_ = current_ - x;
		return *this;
	};

	Iterator operator+(int x) const
	{
		return Iterator(data_, first_, capacity_, current_ + x);
	};

	Iterator operator-(difference_type x)
	{
		return Iterator(data_, first_, capacity_, current_ - x);
	};

	bool operator!=(Iterator const& other) const
	{
		return other.current_ != current_;
	};

	bool operator==(Iterator const& other) const
	{
		return not (*this != other);
	};

	bool operator<(const Iterator& other) const
	{
		return other.current_ < current_;
	};

	bool operator>(const Iterator& other) const
	{
		return other.current_ > current_;
	};

	bool operator>=(const Iterator& other) const
	{
		return !(other < *this);
	};

	bool operator<=(const Iterator& other) const
	{
		return !(*this < other);
	};

	Iterator& operator++()
	{
		current_++;
		return *this;
	};

	Iterator operator++(int)
	{
		Iterator buffer(*this);
		++buffer;
		return buffer;
	};

	Iterator operator--()
	{
		current_--;
		return *this;
	};

	Iterator& operator--(int)
	{
		Iterator buffer(*this);
		--buffer;
		return buffer;
	};

	friend Iterator operator+(Iterator::difference_type x, Iterator it)
	{
		return it + x;
	};

	friend Iterator::difference_type operator-(const Iterator& it1, const Iterator& it2)
	{
		return it1.current_ - it2.current_;
	};
};

template <typename T>
class CircularBuffer
{
 private:
	T* data_;
	unsigned int capacity_;
	unsigned int first_;
	unsigned int items_;

 public:
	CircularBuffer(int capacity)
		: capacity_(capacity), first_(0), items_(0)
	{
		data_ = new T[capacity + 1];
	};

	void addLast(T x)
	{
		data_[index(first_ + items_)] = x;
		if (items_ < capacity_)
			items_++;
	};

	void addFirst(T x)
	{
		if (first_ == 0)
			first_ = capacity_ - 1;
		else
			first_--;

		data_[first_] = x;

		if (items_ < capacity_)
			items_++;
	};

	T& first() const
	{
		if (items_ == 0)
			throw std::runtime_error("Empty buffer.");
		return data_[first_];
	};

	T& last() const
	{
		if (items_ == 0)
			throw std::runtime_error("Empty buffer.");
		return data_[index(first_ + items_ - 1)];
	};

	void delFirst()
	{
		first_ = index(first_ + 1);
		items_--;
	};

	void delLast()
	{
		items_--;
	};

	T& operator[](unsigned int i)
	{
		if (i < items_ and i < capacity_)
			return data_[index(first_ + i)];
		else
		{
			if (items_ == 0)
				throw std::range_error("Out of Range. Buffer is empty");
			std::string error_message = "Out of Range. Index: ";
			error_message += std::to_string(i);
			error_message += ". Buffer capacity is ";
			error_message += std::to_string(items_);
			error_message += ".";
			throw std::out_of_range(error_message);
		}
	};

	T& operator[](unsigned int i) const
	{
		if (i < capacity_ and i < items_)
			return data_[index(first_ + i)];
		else
		{
			std::string error_message = "Element";
			error_message += std::to_string(i);
			error_message += " doesn't exist.";
			throw std::range_error(error_message);
		}

	};

	void changeCapacity(unsigned int new_capacity)
	{
		T* buf = new T[new_capacity];
		unsigned int i = first_;
		unsigned int j = i;

		for (unsigned int k = 0; k < items_; k++)
		{
			buf[j] = data_[i];

			i = (i + 1) % capacity_;
			j = (j + 1) % new_capacity;
		}

		capacity_ = new_capacity;
		delete[] data_;
		data_ = buf;
	};

	friend class Iterator<T>;
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;

	iterator begin() const
	{
		return iterator(data_, first_, capacity_, 0);
	};

	iterator end() const
	{
		return iterator(data_, first_, capacity_, items_);
	};

	int index(int i) const
	{
		return i % capacity_;
	}
};
