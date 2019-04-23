#include "NewsFeed.h"
#include <stdexcept>
using namespace std;

NewsFeed::NewsFeed() : heap(nullptr), n(0), capacity(10) {
	heap = new Headline[capacity];
}


NewsFeed::~NewsFeed() {
	delete[] heap;
}

void NewsFeed::enqueue(Headline headline, Story story, Staleness stale) {
	if (stories.has(headline))
		throw invalid_argument("Headline already in use");
	stories.add(headline, story);
	staleness.add(headline, stale);
	if (n == capacity)
		resize();
	heap[++n] = headline;
	locations.add(headline, n);
	bubble(n);
}

void NewsFeed::dequeue() {
	if (empty())
		throw std::invalid_argument("dequeue from empty heap");
	swap(root(), n--);
	percolate(root());
}

size_t NewsFeed::root() {
	return 1;
}

size_t NewsFeed::parent(size_t child) {
	return child / 2;
}

size_t NewsFeed::left(size_t p) {
	return p * 2;
}

size_t NewsFeed::right(size_t p) {
	return left(p) + 1;
}

void NewsFeed::bubble(size_t child) {
	while (!is_root(child) && value(child) < value(parent(child))) {
		size_t p = parent(child);
		swap(child, p);
		child = p;
	}
}

void NewsFeed::percolate(size_t p) {
	while (!is_leaf(p)) {
		size_t child = left(p);
		if (has_right(p) && value(right(p)) < value(child))
			child = right(p);
		if (value(p) <= value(child))
			return;
		swap(child, p);
		p = child;
	}
}

NewsFeed::Staleness NewsFeed::value(size_t i) const {
	return weight(heap[i]);
}

void NewsFeed::swap(size_t i, size_t j) {
	std::swap(heap[i], heap[j]);
	locations.add(heap[i], i);
	locations.add(heap[j], j);
}

bool NewsFeed::valid(size_t i) const {
	return i > 0 && i <= n;
}

bool NewsFeed::is_root(size_t i) const {
	return !valid(parent(i));
}

bool NewsFeed::is_leaf(size_t i) const {
	return !valid(left(i));
}

bool NewsFeed::has_right(size_t p) const {
	return valid(right(p));
}

void NewsFeed::resize() {
	Headline *oldheap = heap;
	capacity = 2 * capacity + 17;
	heap = new Headline[capacity + 1]; // the +1 is b/c we don't use heap[0]
	for (size_t i = 1; i <= n; i++)
		heap[i] = oldheap[i];
	delete[] oldheap;
}

NewsFeed::Headline NewsFeed::peek() const {
	return heap[root()];
}

bool NewsFeed::empty() const {
	return n == 0;
}

NewsFeed::Staleness NewsFeed::weight(Headline headline) const {
	const auto &map = staleness;
	return map.get(headline);
}

void NewsFeed::reweight(Headline headline, Staleness stale) {
	Staleness w = weight(headline);
	staleness.add(headline, stale);
	if (stale < w)
		bubble(locations.get(headline));
	else if (w < stale)
		percolate(locations.get(headline));
}

NewsFeed::Story NewsFeed::get(Headline headline) const {
	const auto &map = stories;  // force using the const version of the DictHash::get() method
	return map.get(headline);
}

NewsFeed::const_iterator NewsFeed::begin() const {
	return stories.begin();
}

NewsFeed::const_iterator NewsFeed::end() const {
	return stories.end();
}
