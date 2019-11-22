#include <utility>
#include <vector>

template<typename KeyType, typename ValueType>
class Heap4
{
  public:
    using KeyValueType = std::pair<KeyType, ValueType>;

	bool empty() const noexcept {
		return (this->heap).empty();
	}

	void insert(KeyType const & key, ValueType const & value) {
		this->insert(std::make_pair(key, value));
	}

	void insert(KeyValueType const & key_value) {		
		(this->heap).push_back(key_value);
		this->heapifyUp((this->heap).size() - 1);
	}

	KeyValueType const & peek() const {
		if (this->heap.empty()) {
			throw std::logic_error("It's empty.");
		}
		return (this->heap)[0];
	}

	KeyValueType pop() noexcept {
		KeyValueType temp = (this->heap)[0];
		(this->heap)[0] = this->heap[this->size() - 1];
		this->heapifyDown(0);
		this->heap.pop_back();
	}

	size_t size() const noexcept {
		return this->heap.size();
	}

	template<typename StreamType>
	void print(StreamType& stream) const {
		if (this->heap.empty()) {
			return;
		}
		this->printHelp(stream, 0, 0);
	}
  private:
	std::vector<KeyValueType> heap;
	template<typename StreamType>
	void printHelp(StreamType& stream, const unsigned int index, const unsigned int level) const {
		for (unsigned int i = 0; i < level * 10; ++i) {
			stream << " ";
		}
		stream << (this->heap)[index].first << ": " << (this->heap)[index].second;
		stream << "\n";
		int child = -1;
		for (unsigned int i = 1; i <= 4; ++i) {
			child = this->child(index, i);
			if (child > -1) {
				this->printHelp(stream, child, level + 1);
			}
		}
	}
	int child(const unsigned int index, const unsigned int childNum) const {
		unsigned int ind = index * 4 + childNum;
		return (ind < this->size()) ? ind : -1;
	}
	int parent(const unsigned int index) const {
		return (index > 0) ? (index - 1) / 4 : -1;
	}
	void heapifyUp(const int index) {
		if (index <= 0) {
			return;
		}
		int parentInd = -1;
		parentInd = this->parent(index);
		if ((this->heap)[parentInd].first < (this->heap)[index].first) {
			KeyValueType temp = (this->heap)[parentInd];
			(this->heap)[parentInd] = (this->heap)[index];
			(this->heap)[index] = temp;
			this->heapifyUp(parentInd);
		}
	}
	void heapifyDown(const int index) {
		int childIndex = -1;
		unsigned int maxChildIndex = index;
		for (int i = 1; i <= 4; ++i) {
			childIndex = this->child(index, i);
			if (childIndex == -1) {
				return;
			}
			if ((this->heap)[maxChildIndex].first < (this->heap)[childIndex].first) {
				maxChildIndex = childIndex;
			}
		}
		if (maxChildIndex != index) {
			KeyValueType temp = (this->heap)[index];
			(this->heap)[index] = (this->heap)[maxChildIndex];
			(this->heap)[maxChildIndex] = temp;
			this->heapifyDown(maxChildIndex);
		}
	}
};
