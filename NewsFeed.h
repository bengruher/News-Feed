#pragma once
#include "DictHash.h"
#include <string>
class NewsFeed {
public:
	typedef std::string Headline;
	typedef std::string Story;
	typedef int Staleness;
	typedef std::hash<std::string> HeadlineHasher;
	typedef DictHash<Headline, Story, HeadlineHasher>::const_iterator const_iterator;

	NewsFeed();
	NewsFeed(const NewsFeed& other) = delete;
	NewsFeed& operator=(const NewsFeed& other) = delete;
	NewsFeed(NewsFeed&& temp) = delete;
	NewsFeed& operator=(NewsFeed&& temp) = delete;
	~NewsFeed();

	void enqueue(Headline headline, Story story, Staleness staleness);
	void dequeue();
	Headline peek() const;
	bool empty() const;
	Staleness weight(Headline headline) const;
	void reweight(Headline headline, Staleness staleness);
	Story get(Headline headline) const;
	const_iterator begin() const;
	const_iterator end() const;

private:
	typedef size_t HeapLocation;

	DictHash<Headline, Story, HeadlineHasher>        stories;
	DictHash<Headline, Staleness, HeadlineHasher>    staleness;
	DictHash<Headline, HeapLocation, HeadlineHasher> locations;

	Headline *heap;   // specialized heap holds headlines; priority is looked up in staleness dict
	size_t n;         // number of items in the heap
	size_t capacity;  // allocated size of heap array

	void bubble(size_t child);
	void percolate(size_t p);
	Staleness value(size_t i) const;
	void swap(size_t i, size_t j);
	bool valid(size_t i) const;
	bool is_root(size_t i) const;
	bool is_leaf(size_t i) const;
	bool has_right(size_t p) const;
	void resize();

	static size_t root();
	static size_t parent(size_t child);
	static size_t left(size_t p);
	static size_t right(size_t p);
};

