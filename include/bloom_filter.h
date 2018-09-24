#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>

namespace ads {

  class bloom_filter {
    
    public:

      /* Construct a bloom filter with correct number of hashes for a false positive rate. */
      bloom_filter(int count, double falsePositiveRate);

      /* Construct a bloom filter of set size, and some initialising entries. */
      bloom_filter(int count, double falsePositiveRate, std::vector<std::string> elements);

      /* Initialiser-List Constructor */
      bloom_filter(int count, double falsePositiveRate, const std::initializer_list<std::string>& elements);

      /* Insert an Element. */
      void insert(const std::string& element);

      /* Returns if an Element Exists in the Tree */
      bool find(const std::string& element);

      /* Clears all Elements of the Binary Tree */
      void clear();

    private:

      std::vector<bool> hashSet;

  };

} // ads

#endif