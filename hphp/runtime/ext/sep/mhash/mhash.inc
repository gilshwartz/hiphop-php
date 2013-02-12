// @generated by "php idl.php inc {input.idl.php} {output.inc}"

#if EXT_TYPE == 0
"mhash", T(Variant), S(0), "hash", T(Int64), NULL, S(0), NULL, S(0), "data", T(String), NULL, S(0), NULL, S(0), "key", T(String), "N;", S(2), "null", S(0), NULL, S(16384), "/**\n * ( excerpt from http://php.net/manual/en/function.mhash.php )\n *\n * mhash() applies a hash function specified by hash to the data.\n *\n * @hash       int     The hash id. One of the MHASH_XXX constants.\n * @data       string  The user input, as a string.\n * @key        string  If specified, the function will return the resulting\n *                     HMAC instead. HMAC is keyed hashing for message\n *                     authentication, or simply a message digest that\n *                     depends on the specified key. Not all algorithms\n *                     supported in mhash can be used in HMAC mode.\n *\n * @return     mixed   Returns the resulting hash (also called digest) or\n *                     HMAC as a string, or FALSE on errors. OpenSSL\n *                     mhash_keygen_s2k Last updated: Fri, 06 Aug 2010 \240\n */", 
"mhash_get_hash_name", T(Variant), S(0), "hash", T(Int64), NULL, S(0), NULL, S(0), NULL, S(16384), "/**\n * ( excerpt from http://php.net/manual/en/function.mhash-get-hash-name.php\n * )\n *\n * Gets the name of the specified hash.\n *\n * @hash       int     The hash id. One of the MHASH_XXX constants.\n *\n * @return     mixed   Returns the name of the hash or FALSE, if the hash\n *                     does not exist.\n */", 
"mhash_count", T(Int64), S(0), NULL, S(16384), "/**\n * ( excerpt from http://php.net/manual/en/function.mhash-count.php )\n *\n * Gets the highest available hash id.\n *\n * @return     int     Returns the highest available hash id. Hashes are\n *                     numbered from 0 to this hash id.\n */", 
"mhash_get_block_size", T(Variant), S(0), "hash", T(Int64), NULL, S(0), NULL, S(0), NULL, S(16384), "/**\n * ( excerpt from\n * http://php.net/manual/en/function.mhash-get-block-size.php )\n *\n * Gets the size of a block of the specified hash.\n *\n * @hash       int     The hash id. One of the MHASH_XXX constants.\n *\n * @return     mixed   Returns the size in bytes or FALSE, if the hash does\n *                     not exist.\n */", 
"mhash_keygen_s2k", T(Variant), S(0), "hash", T(Int64), NULL, S(0), NULL, S(0), "password", T(String), NULL, S(0), NULL, S(0), "salt", T(String), NULL, S(0), NULL, S(0), "bytes", T(Int64), NULL, S(0), NULL, S(0), NULL, S(16384), "/**\n * ( excerpt from http://php.net/manual/en/function.mhash-keygen-s2k.php )\n *\n * Generates a key according to the hash given a user provided password.\n * This is the Salted S2K algorithm as specified in the OpenPGP document\n * (\273 RFC 2440).\n * Keep in mind that user supplied passwords are not really suitable to be\n * used as keys in cryptographic algorithms, since users normally choose\n * keys they can write on keyboard. These passwords use only 6 to 7 bits\n * per character (or less). It is highly recommended to use some kind of\n * transformation (like this function) to the user supplied key.\n *\n * @hash       int     The hash id used to create the key. One of the\n *                     MHASH_XXX constants.\n * @password   string  User supplied password.\n * @salt       string  Must be different and random enough for every key\n *                     you generate in order to create different keys. That\n *                     salt must be known when you check the keys, thus it\n *                     is a good idea to append the key to it. Salt has a\n *                     fixed length of 8 bytes and will be padded with\n *                     zeros if you supply less bytes.\n * @bytes      int     The key length, in bytes.\n *\n * @return     mixed   Returns the generated key as a string, or FALSE on\n *                     error.\n */", 

#elif EXT_TYPE == 1

#elif EXT_TYPE == 2

#endif