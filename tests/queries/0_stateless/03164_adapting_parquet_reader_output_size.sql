-- Tags: no-fasttest, no-parallel

DROP TABLE IF EXISTS test_parquet;
CREATE TABLE test_parquet (col1 String, col2 String, col3 String, col4 String, col5 String, col6 String, col7 String) ENGINE=File(Parquet);
INSERT INTO test_parquet SELECT rand(),rand(),rand(),rand(),rand(),rand(),rand() FROM numbers(100000);
SELECT max(blockSize()) FROM test_parquet;

DROP TABLE IF EXISTS test_parquet;
CREATE TABLE test_parquet (col1 String, col2 String, col3 String, col4 String, col5 String, col6 String, col7 String) ENGINE=File(Parquet) settings input_format_parquet_max_block_rows=16;
INSERT INTO test_parquet SELECT rand(),rand(),rand(),rand(),rand(),rand(),rand() FROM numbers(100000);
SELECT max(blockSize()) FROM test_parquet;

DROP TABLE IF EXISTS test_parquet;
CREATE TABLE test_parquet (col1 String, col2 String, col3 String, col4 String, col5 String, col6 String, col7 String) ENGINE=File(Parquet) settings input_format_parquet_prefer_block_bytes=30;
INSERT INTO test_parquet SELECT rand(),rand(),rand(),rand(),rand(),rand(),rand() FROM numbers(100000);
SELECT max(blockSize()) FROM test_parquet;

DROP TABLE IF EXISTS test_parquet;
CREATE TABLE test_parquet (col1 String, col2 String, col3 String, col4 String, col5 String, col6 String, col7 String) ENGINE=File(Parquet) settings input_format_parquet_prefer_block_bytes=30000;
INSERT INTO test_parquet SELECT rand(),rand(),rand(),rand(),rand(),rand(),rand() FROM numbers(100000);
SELECT max(blockSize()) FROM test_parquet;

DROP TABLE IF EXISTS test_parquet;