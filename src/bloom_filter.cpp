#include <set>
#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include "../include/bloom_filter.h"

using namespace ads;

bloom_filter::bloom_filter(int num_entries, double false_postitive_rate) {
  /* (-num_entries * log_2(false_postitive_rate)) / ln2 */
  int num_bits    = std::ceil((-1 * num_entries * std::log2(false_postitive_rate)) / std::log(2));
  
  /* ( num_bits / num_entries ) * ln2 */
  int num_hashes  = std::ceil((num_bits / (double)num_entries) * std::log(2));

  bits.reserve(num_bits);
  this->num_hashes = num_hashes;
}