#pragma once


template<typename T>
class vector {

	using iterator = T*;
	using const_iterator = const T*;


public:
	vector() 
	{
		ReAllocate(2);
	}

	vector(const std::initializer_list<T> list)
	{
		ReAllocate(list.size());

		for (const auto& item : list)
		{
			PushBack(item);
		}
	}

	~vector()
	{
		clear();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}


	void ReAllocate(size_t newCapacity)
	{
		T* newData = (T*)::operator new (newCapacity * sizeof(T));

		if (newCapacity < m_LastData)
			m_LastData = newCapacity;

		for (size_t i = 0; i < m_LastData; i++)
		{
			new (newData + i) T(std::move(m_Data[i]));
		}

		::operator delete(m_Data, m_Capacity * sizeof(T));
		m_Data = newData;
		m_Capacity = newCapacity;
	}

	void PushBack(const T& val)
	{
		if (m_LastData >= m_Capacity)
			ReAllocate(m_Capacity + m_Capacity / 2);

		m_Data[m_LastData] = val;
		m_LastData++;
	}

	void PushBack(T&& val)
	{
		if (m_LastData >= m_Capacity)
			ReAllocate(m_Capacity + m_Capacity / 2);

		m_Data[m_LastData] = std::move(val);
		m_LastData++;
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		if (m_LastData >= m_Capacity)
			ReAllocate(m_Capacity + m_Capacity / 2);

		new(&m_Data[m_LastData]) T(std::forward<Args>(args)...);
		return m_Data[m_LastData++];
	}

	void PopBack()
	{
		if (m_LastData > 0)
		{
			m_LastData--;
			m_Data[m_LastData].~T();
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_LastData; i++)
			m_Data[i].~T();

		m_LastData = 0;
	}

	T* data()
	{
		return m_Data;
	}

	constexpr const T* data() const noexcept
	{
		return m_Data;
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
		return m_Data + m_LastData;
	}

	const_iterator end() const
	{
		return m_Data + m_LastData;
	}

	const_iterator cend() const
	{
		return m_Data + m_LastData;
	}

	size_t size() const
	{
		return m_LastData;
	}

	T& at(size_t index)
	{
		if (index < m_LastData)
			return m_Data[index];
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	

private:

	// Data vector
	T* m_Data = nullptr;
	// Index of the last valid data in the vector
	size_t m_LastData = 0;
	// Size of the vector
	size_t m_Capacity = 0;


};
