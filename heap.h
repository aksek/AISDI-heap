#include <utility>
#include <vector>

template<typename KeyType, typename ValueType>
class Heap4 {
  public:
    using KeyValueType = std::pair<KeyType, ValueType>;
	using size_type = typename std::vector<KeyValueType>::size_type;

	bool empty() const noexcept {
		return this->heap.empty();
	}

	void insert(KeyType const &key, ValueType const &value) {
		this->insert(std::make_pair(key, value));
	}

	void insert(KeyValueType const &key_value) {		
		this->heap.push_back(key_value);
		this->heapifyUp(this->heap.size() - 1);
	}

	KeyValueType const &peek() const {
		if (this->heap.empty()) {
			throw std::logic_error("The heap is empty");
		}
		return this->heap[0];
	}

	void swap(const size_type i1, const size_type i2) {
		KeyValueType temp = this->heap[i1];
		this->heap[i1] = this->heap[i2];
		this->heap[i2] = temp;
	}

	KeyValueType pop() {
		if (this->empty()) {
			throw std::logic_error("The heap is empty");
		}
		KeyValueType deletedEl = this->heap[0];
		this->swap(0, this->size() - 1);
		this->heap.pop_back();
		this->heapifyDown(0);
		return deletedEl;
	}

	size_t size() const noexcept {
		return this->heap.size();
	}

	template<typename StreamType>
	void print(StreamType& stream) const {
		if (this->empty()) {
			return;
		}
		this->printHelp(stream, 0, 0);
	}

  private:
	std::vector<KeyValueType> heap;

	template<typename StreamType>
	void printHelp(StreamType& stream, const size_type index, const unsigned int level) const {
		for (unsigned int i = 0; i < level; ++i) {
			stream << "       ";
		}
		stream << this->heap[index].first << ": " << this->heap[index].second << '\n';
		size_type child = 0;
		for (size_t i = 1; i <= 4; ++i) {
			try {
				child = this->child(index, i);
			} catch(std::logic_error &ex) {
				break;
			}
			this->printHelp(stream, child, level + 1);
		}
	}
	
	size_type child(const size_type index, const size_t childNum) const {
		size_type ind = index * 4 + childNum;
		if (ind >= this->size()) {
			throw std::logic_error("There is no child");
		}
		return ind;
	}

	size_type parent(const size_type index) const {
		if (!index) {
			throw std::logic_error("There is no parent");
		}
		return (index - 1) / 4;
	}

	void heapifyUp(const size_type index) {
		if (!index) {
			return;
		}
		size_type parentInd = this->parent(index);		
		if (this->heap[parentInd].first < this->heap[index].first) {
			this->swap(parentInd, index);
			this->heapifyUp(parentInd);
		}
	}

	void heapifyDown(const size_type index) {
		size_type childIndex = 0;
		size_type maxChildIndex = index;
		for (size_t i = 1; i <= 4; ++i) {
			try {
				childIndex = this->child(index, i);
			} catch (std::logic_error &ex) {
				break;
			}
			if (this->heap[maxChildIndex].first < this->heap[childIndex].first) {
				maxChildIndex = childIndex;
			}
		}
		if (maxChildIndex != index) {
			this->swap(index, maxChildIndex);
			this->heapifyDown(maxChildIndex);
		}
	}
};