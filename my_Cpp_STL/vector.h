#pragma once


template<typename T>
class vector {

public:
	vector() 
	{
		ReAllocate(2);
	}


	void ReAllocate(size_t newCapacity)
	{
		T* newData = (T*)::operator new (newCapacity * sizeof(T));

		if (newCapacity < m_LastData)
			m_LastData = newCapacity;

		for (size_t i = 0; i < m_LastData; i++)
		{
			newData[i] = std::move(m_Data[i]);
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

	template<class... Args>
	void emplace_back(Args&&... args)
	{
		if (m_LastData >= m_Capacity)
			ReAllocate(m_Capacity + m_Capacity / 2);

		new(&m_Data[m_LastData]) T(std::forward<Args>(args)...);
	}

	void PopBack()
	{
		if (m_LastData > 0)
		{
			m_LastData--;
			m_Data[m_LastData].~T();
		}
	}

	size_t size() const
	{
		return m_LastData;
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
