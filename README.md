# HITS and SALSA

Implementation of the HITS and SALSA classification algorithms on sparse matrix for highly parallel systems.

## Build
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Data Generation
1. First download [metadata.json.gz](http://snap.stanford.edu/data/amazon/productGraph/metadata.json.gz) from [http://jmcauley.ucsd.edu/data/amazon/links.html](http://jmcauley.ucsd.edu/data/amazon/links.html)

2. Extract file : \
`gunzip metadata.json.gz`

1. Clean the input file (clean single quotes): \
`scripts/clean.py metadata.json clean_metadata.json`
> Nb : Since the `metadata.json` file contains 9.4 million entries, you can extract a sample using, for example: `head -n 10000 metadata.json > sample.json` to extract the first 10000 entries

1. Finaly further cleaning (make it a JSON readable file) \
`sed -i -f clean.sed clean_metadata.json`
