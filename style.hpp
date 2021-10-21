		

// v1 from STL vscode
allocator_type get_allocator() const
	{ return alloc_; }

size_type	size() const
	{ return size_; }

size_type	max_size() const
	{ return alloc_.max_size(); }

size_type	capacity() const
	{ return capacity_; }
	
bool		empty() const
	{ return size_ == 0;}


// v2 mine
allocator_type get_allocator() const { return alloc_; }

size_type	size() const { return size_; }

size_type	max_size() const { return alloc_.max_size(); }

size_type	capacity() const { return capacity_; }
	
bool		empty() const { return size_ == 0;}


// v3 kinda C
allocator_type get_allocator() const {
	return alloc_;
}

size_type	size() const {
	return size_;
}

size_type	max_size() const {
	return alloc_.max_size();
}

size_type	capacity() const {
	return capacity_;
}

bool		empty() const {
	return size_ == 0;
}
