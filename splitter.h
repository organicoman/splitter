// container_splitter.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <cstring> //memcpy; memset

namespace helper
{
	template<typename T>
	class is_container : public std::false_type {};
	
	template<typename U, size_t N> class is_container<std::array<U, N>> : public std::true_type {};
	template<typename U> class is_container<std::vector<U>> : public std::true_type {};
	template<typename U> class is_container<std::deque<U>> : public std::true_type {};
	template<typename U> class is_container<std::list<U>> : public std::true_type {};
	template<typename U> class is_container<std::forward_list<U>> : public std::true_type {};
	template<typename U> class is_container<std::set<U>> : public std::true_type {};
	template<typename U, typename V> class is_container<std::map<U, V>> : public std::true_type {};
	template<typename U> class is_container<std::unordered_set<U>> : public std::true_type {};
	template<typename U, typename V> class is_container<std::unordered_map<U, V>> : public std::true_type {};

	template<typename T> 
	inline constexpr bool is_container_v = is_container<T>::value;

	template<typename Container>
	class container_splitter;

	template<typename Container>
	class container_slice;
}

template<typename Container>
class helper::container_slice : public Container
{
	static_assert(helper::is_container_v<Container>);

	typename Container::iterator m_begin;
	typename Container::iterator m_end;

public:
	using Container::Container; //import all constructors from base class

	container_slice(const Container& src, typename Container::iterator beg, typename Container::iterator end) :
		m_begin(beg), m_end(end)
	{
		/*
		 * clone the bits from the source container into the memory location allocated to the base class of this
		 * instance.
		 * the assumption here is that the base class `Container` is laid out starting memory
		 * location 0. if the memory layout of this C++ object changes, this will not hold anymore!
		 */
		std::memcpy((void*)this, (void*)&src, sizeof(Container)); 
	}
	void detach()
	{
		// emplacement new at the location of this instance
		new (this) container_slice(m_begin, m_end); // parenthisis instead of curly braces (see emplacement new Docs)

		// a copy assignement operator would work too
		// *this = container_slice{m_begin, m_end};
	}

	~container_slice()
	{
		// to avoid double free
		std::memset((void*)this, 0, sizeof(Container));
	}

	// and this is how you constraint the bounds of the container
	typename Container::iterator begin() noexcept { return m_begin; }
	typename Container::iterator begin() const noexcept { return m_begin; }
	typename Container::iterator end() noexcept { return m_end; }
	typename Container::iteratpr end() const noexcept { return m_end; }

	const typename Container::iterator cbegin() noexcept { return m_begin; }
	const typename Container::iterator cend() noexcept { return m_end; }
};

template<typename Container>
class helper::container_splitter
{
public:
	static_assert(helper::is_container_v<Container>, "the template parameter is not an STL container\n");

	using value_type = typename Container::value_type;
	using difference_type = typename Container::difference_type;
	using reference = value_type&;
	using const_reference = const reference;
	using pointer = value_type*;
	using const_pointer = const pointer;
	using iterator = typename Container::iterator;
	using const_iterator = const iterator;
	using reverse_iterator = typename Container::reverse_iterator;
	
private:
	iterator startPos;
	iterator m_begin;
	reverse_iterator m_rbegin;
	value_type m_separator;
	helper::container_slice<Container> m_currWord;
	bool m_atEnd;

public:
	container_splitter() = delete;
	explicit constexpr container_splitter(const_iterator& begin, const_reference sep = value_type{}) noexcept;
	//explicit constexpr container_splitter(iterator& begin, const value_type& sep = value_type{}) noexcept;
	container_splitter(const container_splitter& other) noexcept = default;
	container_splitter(container_splitter&& other) noexcept = default;

	container_splitter& operator=(const container_splitter& other) noexcept = default;
	container_splitter& operator=(container_splitter&& other) noexcept = default;

	helper::container_slice<Container> next_word() noexcept;.
	helper::container_slice<Container> prev_word() noexcept;
	helper::container_slice<Container> curr_word() noexcept;

	void setSeparator(const value_type& sep) noexcept;
	value_type getSeparator() const noexcept;

	bool atEnd() const noexcept;
	bool isFullsize() const noexcept;

	void reset() noexcept;
	void rewindTo(const_iterator& pos) noexcept;

	helper::container_slice<Container> operator+=(const ptrdiff_t stride) noexcept;
	helper::container_slice<Container> operator++() noexcept; // pre increment
	helper::container_slice<Container> operator++(const ptrdiff_t) noexcept; //post increment
};

template<typename Container>
inline constexpr helper::container_splitter<Container>::container_splitter(const_iterator& begin, const_reference sep) noexcept:
	startPos(begin), m_begin(begin), m_rbegin(std::reverse_iterator(begin)),
	m_separator(sep), m_currWord(container_slice<Container>{}), m_atEnd(false)
{
}

template<typename Container>
inline helper::container_slice<Container> helper::container_splitter<Container>::next_word() noexcept
{
	auto end = m_begin.
	auto next = std::find(m_begin, )
	return helper::container_slice<Container>();
}
