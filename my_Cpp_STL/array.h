#pragma once

template<typename T, size_t N>
class array {

	using iterator = T*;
	using const_iterator = const T*;

public:

	array() = default;

	array(std::initializer_list<T>&& list)
	{
		if (list.size() != N)
			throw std::invalid_argument("Initializer list size does not match array size");
		
		auto it = list.begin();
		for (size_t i = 0; i < N; ++i) {
			m_Data[i] = std::move(*it);
			++it;
		}
	}

	T& at(size_t index)
	{
		if (index < N)
			return m_Data[index];
	}

	constexpr T& at(size_t index) const
	{
		if (index < N)
			return m_Data[index];
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	constexpr T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	T& front()
	{
		return m_Data[0];
	}

	T& back()
	{
		return m_Data[N - 1];
	}

	constexpr size_t size() const
	{
		return N;
	}

	constexpr size_type max_size() const noexcept
	{
		return N;
	}

	constexpr bool empty() const noexcept
	{
		return begin() == end();
	}

	constexpr void fill(const T& value)
	{
		for (size_t i = 0; i < N; i++)
			m_Data[i] = value;
	}


	iterator begin()
	{
		return m_Data;
	}
	const_iterator begin() const
	{
		return m_Data;
	}

	const_iterator cbegin() const
	{
		return m_Data;
	}

	iterator end()
	{
		return &(m_Data[N]);
	}

	const_iterator end() const
	{
		return &(m_Data[N]);
	}

	const_iterator cend() const
	{
		return  &(m_Data[N]);
	}




private:

	T m_Data[N];


};