#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <string>
#include <vector>

namespace ads {

class bloom_filter {

public:
  /* Construct a bloom filter with correct number of hashes for a false positive
   * rate. */
  bloom_filter(const int num_entries, const double false_positive_rate);

  /* Construct a bloom filter of set size, and some initialising entries. */
  bloom_filter(const int num_entries, const double false_positive_rate,
               const std::vector<std::string> &entries);

  /* Initialiser-List Constructor */
  bloom_filter(const int num_entries, const double false_positive_rate,
               const std::initializer_list<std::string> &entries);

  /* Copy Constructor */
  bloom_filter(const bloom_filter &copy);

  /* Assignment Operator */
  bloom_filter &operator=(const bloom_filter &rhs);

  /* Insert an Element. */
  void insert(const std::string &entry);

  /* Returns if an Element Exists in the Tree */
  bool find(const std::string &entry) const;

  /* Clears all Elements of the Binary Tree */
  void clear();

  /* Returns a String Representation of the Bloom Filter. */
  std::string dump() const;

private:
  int num_hashes;
  std::vector<bool> bits;

  void validate_args(const int num_entries,
                     const double false_positive_rate) const;
  int get_num_bits(const int num_entries,
                   const double false_positive_rate) const;
  int get_num_hashes(const int num_entries, const int num_bits) const;
};

} // namespace ads

#endif