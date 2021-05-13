#ifndef _PREDICATE_HPP_
#define _PREDICATE_HPP_

#include <iostream>

using namespace std;

template <class Iterator, class Predicate>
bool allOf(Iterator first, Iterator last, Predicate predicate)
{
	for (Iterator it = first; it != last; it++)
	{
		if (not predicate(*it))
			return false;
	}

	return true;
}


template <class Iterator, class Predicate>
bool anyOf(Iterator first, Iterator last, Predicate predicate)
{
	for (Iterator it = first; it != last; it++)
	{
		if (predicate(*it))
			return true;
	}

	return false;
}


template <class Iterator, class Predicate>
bool noneOf(Iterator first, Iterator last, Predicate predicate)
{
	return not anyOf(first, last, predicate);
}


template <class Iterator, class Predicate>
bool oneOf(Iterator first, Iterator last, Predicate predicate)
{
	bool used = false;

	for (Iterator it = first; it != last; it++)
	{
		if (predicate(*it))
		{
			if (used)
				return false;

			used = true;
		}
	}

	return used;
}


template <class Iterator, class Predicate = less<>>
bool isSorted(Iterator first, Iterator last, Predicate predicate = Predicate())
{
	for (Iterator it = first; it != last - 1; it++)
	{
		if (not predicate(*it, *(it + 1)))
			return false;
	}

	return true;
}


template <class Iterator, class Predicate>
bool isPartitioned(Iterator first, Iterator last, Predicate predicate)
{
	bool part = predicate(*first);
	bool used = false;

	for (Iterator it = first + 1; it != last; it++)
	{
		if (predicate(*it) != part)
		{
			if (used)
				return false;

			used = true;
			part = not part;
		}
	}

	return true;
}


template <class Iterator, class Element>
Iterator findNot(Iterator first, Iterator last, Element element)
{
	for (Iterator it = first; it != last; it++)
	{
		if (element != *it)
			return it;
	}

	return last;
}


template <class Iterator, class Element>
Iterator findBackward(Iterator first, Iterator last, Element element)
{
	Iterator answer = last;

	for (Iterator it = first; it != last; it++)
	{
		if (element == *it)
			answer = it;
	}

	return answer;
}


template <class Iterator, class Predicate>
bool isPalindrome(Iterator first, Iterator last, Predicate predicate)
{
	Iterator left = first;
	Iterator right = --last;

	while (left != right)
	{
		if (not predicate(*left, *right))
			return false;

		if (++left == right)
			break;

		right--;
	}

	return true;
}


#endif //_PREDICATE_HPP_
