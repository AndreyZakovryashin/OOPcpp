template <class T> class XList 
{
private:
	class Element
	{
	public:
		T data;
		Element * prev;
		Element * next;
	};
	Element * first;
public:
	XList()
	{
		first = NULL;
	}
	XList(T & _data)
	{
		first = NULL;
		AddToTop(_data);
	}
	bool Empty() const
	{
		if (first != NULL) 
			return false;
		return true;
	}
	void AddToTop(const T & _data)
	{
		if(Empty())
		{
			first = new Element;
			first->prev = NULL;
			first->next = NULL;
			first->data = _data;
		}
		else
		{
			Element * temp = new Element;
			temp->data = _data;
			temp->prev = NULL; 
			temp->next = first;
			first->prev = temp;
			first = temp;
		}
	}
	void AddToEnd(const T & _data)
	{
		if(Empty())
			AddToTop(_data);
		else
		{
			Element * temp = GetLast();
			Element * last = new Element;
			last->prev = temp;
			last->next = NULL;
			last->data = _data;
			temp->next = last;
		}
	}
	void RemoveFirst()
	{
		if(!Empty())
		{
			Element * temp = first;
			first = first->next;
			delete temp;
		}
		else
			throw std::string("List is empty.");
	}
	void RemoveLast()
	{
		if(!Empty())
		{
			Element * last = GetLast();
			Element * temp = last;
			last = last->prev;
			last->next = NULL;
			delete temp;
		}
		else
			throw std::string("List is empty.");
	}
	void RemoveAll()
	{
		while(!Empty())
		{
			Element * temp = first;
			first = first->next;
			delete temp;
		}
	}
	T * GetValueFirst() const
	{
		if(Empty())
			return NULL;
		return & first->data;
	}
	T * GetValueLast() const
	{
		if(Empty())
			return NULL;
		if(first->next == NULL)
			return GetValueFirst();
		Element * last;
		last = GetLast();
		return & last->data;
	}
	T * GetValue(unsigned int number) const
	{
		if(!Empty())
		{
			if(number >= GetCount())
				throw std::string("GetValue argument too large.");
			if(Empty())
				return NULL;
			Element * temp = first;
			for(unsigned int i = 0; i < number ; ++i)
				temp = temp->next;
			return & temp->data;
		}
		else
			throw std::string("List is empty.");
	}
	
	Element * GetLast() const
	{
		if(!Empty())
		{
			Element * last;
			last = first;
			while(last->next)
				last = last->next;
			return last;
		}
		else
			throw std::string("List is empty.");
	}
	Element * GetFirstFromLast() const // (Task - iterate in both directions)
	{
		if(!Empty())
		{
			Element * temp;
			temp = GetLast();
			while(temp->prev)
				temp = temp->prev;
			return temp;
		}
		else
			throw std::string("List is empty.");
	}
	unsigned int GetCount() const
	{
		unsigned int count = 0;
		Element * temp;
		temp = first;
		while(temp)
		{
			temp = temp->next;
			++count;
		}
		return count;
	}
	~XList()
	{
		RemoveAll();
	}
};