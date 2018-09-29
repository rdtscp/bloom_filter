#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>

namespace ads {

  class bloom_filter {
    
    public:

      /* Construct a bloom filter with correct number of hashes for a false positive rate. */
      bloom_filter(int num_entries, double false_postitive_rate);

      /* Construct a bloom filter of set size, and some initialising entries. */
      bloom_filter(int num_entries, double false_postitive_rate, std::vector<std::string> entries);

      /* Initialiser-List Constructor */
      bloom_filter(int num_entries, double false_postitive_rate, const std::initializer_list<std::string>& entries);

      /* Insert an Element. */
      void insert(const std::string& entry);

      /* Returns if an Element Exists in the Tree */
      bool find(const std::string& entry);

      /* Clears all Elements of the Binary Tree */
      void clear();

    private:

      std::vector<bool> bits;
      int num_hashes;

  };

} // ads

#endif