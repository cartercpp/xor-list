#pragma once

#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <cstdint>
#include <cstddef>

template <typename ValueType>
class xor_list
{
private:

	struct Node
	{
		ValueType m_value;
		std::uintptr_t m_pnx;
	};

public:

	class iterator
	{
	public:

		explicit iterator(std::uintptr_t currentAddress, std::uintptr_t prevAddress) noexcept
			: m_currentAddress(currentAddress), m_prevAddress(prevAddress)
		{
		}

		auto& operator++()
		{
			const Node* node = GetCurrentNode();
			const std::uintptr_t nextAddress = m_prevAddress ^ (node ? node->m_pnx : 0);
			m_prevAddress = m_currentAddress;
			m_currentAddress = nextAddress;
			return *this;
		}

		auto operator++(int)
		{
			const auto temp = *this;
			this->operator++();
			return temp;
		}

		auto& operator--()
		{
			const std::uintptr_t newNextAddress = m_currentAddress;
			m_currentAddress = m_prevAddress;
			const Node* node = GetCurrentNode();
			m_prevAddress = newNextAddress ^ (node ? node->m_pnx : 0);
			return *this;
		}

		auto operator--(int)
		{
			const auto temp = *this;
			this->operator--();
			return temp;
		}

		ValueType& operator*()
		{
			return GetCurrentNode()->m_value;
		}

		const ValueType& operator*() const
		{
			return GetCurrentNode()->m_value;
		}

	private:

		Node* GetCurrentNode()
		{
			return reinterpret_cast<Node*>(m_currentAddress);
		}

		const Node* GetCurrentNode() const
		{
			return reinterpret_cast<const Node*>(m_currentAddress);
		}

		friend bool operator==(iterator lArg, iterator rArg) noexcept
		{
			return lArg.m_currentAddress == rArg.m_currentAddress;
		}

		friend bool operator!=(iterator lArg, iterator rArg) noexcept
		{
			return lArg.m_currentAddress != rArg.m_currentAddress;
		}

		friend class xor_list<ValueType>;

		std::uintptr_t m_currentAddress,
					   m_prevAddress;
	};

	class const_iterator
	{
	public:

		explicit const_iterator(std::uintptr_t currentAddress, std::uintptr_t prevAddress) noexcept
			: m_currentAddress(currentAddress), m_prevAddress(prevAddress)
		{
		}

		auto& operator++()
		{
			const Node* node = GetCurrentNode();
			const std::uintptr_t nextAddress = m_prevAddress ^ (node ? node->m_pnx : 0);
			m_prevAddress = m_currentAddress;
			m_currentAddress = nextAddress;
			return *this;
		}

		auto operator++(int)
		{
			const auto temp = *this;
			this->operator++();
			return temp;
		}

		auto& operator--()
		{
			const std::uintptr_t newNextAddress = m_currentAddress;
			m_currentAddress = m_prevAddress;
			const Node* node = GetCurrentNode();
			m_prevAddress = newNextAddress ^ (node ? node->m_pnx : 0);
			return *this;
		}

		auto operator--(int)
		{
			const auto temp = *this;
			this->operator--();
			return temp;
		}

		const ValueType& operator*() const
		{
			return GetCurrentNode()->m_value;
		}

	private:

		const Node* GetCurrentNode() const
		{
			return reinterpret_cast<const Node*>(m_currentAddress);
		}

		friend bool operator==(const_iterator lArg, const_iterator rArg) noexcept
		{
			return lArg.m_currentAddress == rArg.m_currentAddress;
		}

		friend bool operator!=(const_iterator lArg, const_iterator rArg) noexcept
		{
			return lArg.m_currentAddress != rArg.m_currentAddress;
		}

		friend class xor_list<ValueType>;

		std::uintptr_t m_currentAddress,
					   m_prevAddress;
	};

	class reverse_iterator
	{
	public:

		explicit reverse_iterator(std::uintptr_t currentAddress, std::uintptr_t nextAddress) noexcept
			: m_currentAddress(currentAddress), m_nextAddress(nextAddress)
		{
		}

		auto& operator++()
		{
			const Node* node = GetCurrentNode();
			const std::uintptr_t newNextAddress = m_currentAddress;
			m_currentAddress = m_nextAddress ^ (node ? node->m_pnx : 0);
			m_nextAddress = newNextAddress;
			return *this;
		}

		auto operator++(int)
		{
			const auto temp = *this;
			this->operator++();
			return temp;
		}

		auto& operator--()
		{
			const std::uintptr_t newPrevAddress = m_currentAddress;
			m_currentAddress = m_nextAddress;
			const Node* node = GetCurrentNode();
			m_nextAddress = newPrevAddress ^ (node ? node->m_pnx : 0);
			return *this;
		}

		auto operator--(int)
		{
			const auto temp = *this;
			this->operator--();
			return temp;
		}

		ValueType& operator*()
		{
			return GetCurrentNode()->m_value;
		}

		const ValueType& operator*() const
		{
			return GetCurrentNode()->m_value;
		}

	private:

		Node* GetCurrentNode()
		{
			return reinterpret_cast<Node*>(m_currentAddress);
		}

		const Node* GetCurrentNode() const
		{
			return reinterpret_cast<const Node*>(m_currentAddress);
		}

		friend bool operator==(reverse_iterator lArg, reverse_iterator rArg) noexcept
		{
			return lArg.m_currentAddress == rArg.m_currentAddress;
		}

		friend bool operator!=(reverse_iterator lArg, reverse_iterator rArg) noexcept
		{
			return lArg.m_currentAddress != rArg.m_currentAddress;
		}

		friend class xor_list<ValueType>;

		std::uintptr_t m_currentAddress,
					   m_nextAddress;
	};

	class const_reverse_iterator
	{
	public:

		explicit const_reverse_iterator(std::uintptr_t currentAddress, std::uintptr_t nextAddress) noexcept
			: m_currentAddress(currentAddress), m_nextAddress(nextAddress)
		{
		}

		auto& operator++()
		{
			const Node* node = GetCurrentNode();
			const std::uintptr_t newNextAddress = m_currentAddress;
			m_currentAddress = m_nextAddress ^ (node ? node->m_pnx : 0);
			m_nextAddress = newNextAddress;
			return *this;
		}

		auto operator++(int)
		{
			const auto temp = *this;
			this->operator++();
			return temp;
		}

		auto& operator--()
		{
			const std::uintptr_t newPrevAddress = m_currentAddress;
			m_currentAddress = m_nextAddress;
			const Node* node = GetCurrentNode();
			m_nextAddress = newPrevAddress ^ (node ? node->m_pnx : 0);
			return *this;
		}

		auto operator--(int)
		{
			const auto temp = *this;
			this->operator--();
			return temp;
		}

		const ValueType& operator*() const
		{
			return GetCurrentNode()->m_value;
		}

	private:

		const Node* GetCurrentNode() const
		{
			return reinterpret_cast<const Node*>(m_currentAddress);
		}

		friend bool operator==(const_reverse_iterator lArg, const_reverse_iterator rArg) noexcept
		{
			return lArg.m_currentAddress == rArg.m_currentAddress;
		}

		friend bool operator!=(const_reverse_iterator lArg, const_reverse_iterator rArg) noexcept
		{
			return lArg.m_currentAddress != rArg.m_currentAddress;
		}

		friend class xor_list<ValueType>;

		std::uintptr_t m_currentAddress,
					   m_nextAddress;
	};

	// CONSTRUCTORS & STUFF

	xor_list() noexcept
		: m_headAddress(0), m_tailAddress(0), m_size(0)
	{
	}

	xor_list(std::initializer_list<ValueType> data)
		: xor_list{}
	{
		for (const ValueType& value : data)
			push_back(value);
	}

	xor_list(const xor_list<ValueType>& other)
		: xor_list{}
	{
		for (const ValueType& value : other)
			push_back(value);
	}

	xor_list(xor_list<ValueType>&& other)
		: m_headAddress{ other.m_headAddress }, m_tailAddress{ other.m_tailAddress },
		m_size{ other.m_size }
	{
		other.m_headAddress = other.m_tailAddress = other.m_size = 0;
	}

	auto& operator=(const xor_list<ValueType>& other)
	{
		if (this != &other)
		{
			clear();

			for (const ValueType& value : other)
				push_back(value);
		}

		return *this;
	}

	auto& operator=(xor_list<ValueType>&& other)
	{
		if (this != &other)
		{
			clear();

			m_headAddress = other.m_headAddress;
			m_tailAddress = other.m_tailAddress;
			m_size = other.m_size;

			other.m_headAddress = other.m_tailAddress = other.m_size = 0;
		}

		return *this;
	}

	~xor_list()
	{
		clear();
	}

	// METHODS & STUFF

	iterator begin() noexcept
	{
		return iterator(m_headAddress, 0);
	}

	iterator end() noexcept
	{
		return iterator(0, m_tailAddress);
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(m_headAddress, 0);
	}

	const_iterator end() const noexcept
	{
		return const_iterator(0, m_tailAddress);
	}

	const_iterator cbegin() const noexcept
	{
		return const_iterator(m_headAddress, 0);
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(0, m_tailAddress);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(m_tailAddress, 0);
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(0, m_headAddress);
	}

	const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(m_tailAddress, 0);
	}

	const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(0, m_headAddress);
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(m_tailAddress, 0);
	}

	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(0, m_headAddress);
	}

	void push_front(const ValueType& value)
	{
		Node* newHead = new Node;
		newHead->m_value = value;
		const std::uintptr_t newHeadAddress = reinterpret_cast<std::uintptr_t>(newHead);

		if (m_size == 0)
		{
			newHead->m_pnx = 0;
			m_tailAddress = newHeadAddress;
		}
		else if (m_size == 1)
		{
			Node* head = GetHead();
			head->m_pnx = newHeadAddress;
			newHead->m_pnx = m_headAddress;
		}
		else
		{
			Node* head = GetHead();
			head->m_pnx ^= newHeadAddress;
			newHead->m_pnx = m_headAddress;
		}

		m_headAddress = newHeadAddress;
		++m_size;
	}

	void push_front(ValueType&& value)
	{
		Node* newHead = new Node;
		newHead->m_value = std::move(value);
		const std::uintptr_t newHeadAddress = reinterpret_cast<std::uintptr_t>(newHead);

		if (m_size == 0)
		{
			newHead->m_pnx = 0;
			m_tailAddress = newHeadAddress;
		}
		else if (m_size == 1)
		{
			Node* head = GetHead();
			head->m_pnx = newHeadAddress;
			newHead->m_pnx = m_headAddress;
		}
		else
		{
			Node* head = GetHead();
			head->m_pnx ^= newHeadAddress;
			newHead->m_pnx = m_headAddress;
		}

		m_headAddress = newHeadAddress;
		++m_size;
	}

	void push_back(const ValueType& value)
	{
		Node* newTail = new Node;
		newTail->m_value = value;
		const std::uintptr_t newTailAddress = reinterpret_cast<std::uintptr_t>(newTail);

		if (m_size == 0)
		{
			newTail->m_pnx = 0;
			m_headAddress = newTailAddress;
		}
		else if (m_size == 1)
		{
			Node* tail = GetTail();
			tail->m_pnx = newTailAddress;
			newTail->m_pnx = m_tailAddress;
		}
		else
		{
			Node* tail = GetTail();
			tail->m_pnx ^= newTailAddress;
			newTail->m_pnx = m_tailAddress;
		}

		m_tailAddress = newTailAddress;
		++m_size;
	}

	void push_back(ValueType&& value)
	{
		Node* newTail = new Node;
		newTail->m_value = std::move(value);
		const std::uintptr_t newTailAddress = reinterpret_cast<std::uintptr_t>(newTail);

		if (m_size == 0)
		{
			newTail->m_pnx = 0;
			m_headAddress = newTailAddress;
		}
		else if (m_size == 1)
		{
			Node* tail = GetTail();
			tail->m_pnx = newTailAddress;
			newTail->m_pnx = m_tailAddress;
		}
		else
		{
			Node* tail = GetTail();
			tail->m_pnx ^= newTailAddress;
			newTail->m_pnx = m_tailAddress;
		}

		m_tailAddress = newTailAddress;
		++m_size;
	}

	void pop_front()
	{
		if (m_size == 0)
			throw std::runtime_error{ "XOR List is empty" };
		else if (m_size == 1)
		{
			Node* head = GetHead();
			delete head;
			m_headAddress = m_tailAddress = 0;
		}
		else
		{
			iterator iter{ begin() };
			Node* head = iter.GetCurrentNode();
			++iter;
			Node* newHead = iter.GetCurrentNode();
			const std::uintptr_t newHeadAddress = reinterpret_cast<std::uintptr_t>(newHead);

			newHead->m_pnx ^= reinterpret_cast<std::uintptr_t>(head);
			m_headAddress = newHeadAddress;
			delete head;
		}

		--m_size;
	}

	void pop_back()
	{
		if (m_size == 0)
			throw std::runtime_error{ "XOR List is empty" };
		else if (m_size == 1)
		{
			Node* tail = GetTail();
			delete tail;
			m_headAddress = m_tailAddress = 0;
		}
		else
		{
			reverse_iterator iter{ rbegin() };
			Node* tail = iter.GetCurrentNode();
			++iter;
			Node* newTail = iter.GetCurrentNode();
			const std::uintptr_t newTailAddress = reinterpret_cast<std::uintptr_t>(newTail);

			newTail->m_pnx ^= reinterpret_cast<std::uintptr_t>(tail);
			m_tailAddress = newTailAddress;
			delete tail;
		}

		--m_size;
	}

	void clear()
	{
		while (m_size > 0)
			pop_back();
	}

private:

	Node* GetHead()
	{
		return reinterpret_cast<Node*>(m_headAddress);
	}

	const Node* GetHead() const
	{
		return reinterpret_cast<const Node*>(m_headAddress);
	}

	Node* GetTail()
	{
		return reinterpret_cast<Node*>(m_tailAddress);
	}

	const Node* GetTail() const
	{
		return reinterpret_cast<const Node*>(m_tailAddress);
	}

	std::uintptr_t m_headAddress,
					m_tailAddress;
	std::size_t m_size;
};
