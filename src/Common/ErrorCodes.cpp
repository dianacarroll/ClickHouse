#include <Common/ErrorCodes.h>
#include <chrono>

/** Previously, these constants were located in one enum.
  * But in this case there is a problem: when you add a new constant, you need to recompile
  * all translation units that use at least one constant (almost the whole project).
  * Therefore it is made so that definitions of constants are located here, in one file,
  * and their declaration are in different files, at the place of use.
  *
  * Later it was converted to the lookup table, to provide:
  * - errorCodeToName()
  * - system.errors table
  */

#define APPLY_FOR_ERROR_CODES(M) \
    M(0, OK) \
    M(1, UNSUPPORTED_METHOD) \
    M(2, UNSUPPORTED_PARAMETER) \
    M(3, UNEXPECTED_END_OF_FILE) \
    M(4, EXPECTED_END_OF_FILE) \
    M(6, CANNOT_PARSE_TEXT) \
    M(7, INCORRECT_NUMBER_OF_COLUMNS) \
    M(8, THERE_IS_NO_COLUMN) \
    M(9, SIZES_OF_COLUMNS_DOESNT_MATCH) \
    M(10, NOT_FOUND_COLUMN_IN_BLOCK) \
    M(11, POSITION_OUT_OF_BOUND) \
    M(12, PARAMETER_OUT_OF_BOUND) \
    M(13, SIZES_OF_COLUMNS_IN_TUPLE_DOESNT_MATCH) \
    M(15, DUPLICATE_COLUMN) \
    M(16, NO_SUCH_COLUMN_IN_TABLE) \
    M(17, DELIMITER_IN_STRING_LITERAL_DOESNT_MATCH) \
    M(18, CANNOT_INSERT_ELEMENT_INTO_CONSTANT_COLUMN) \
    M(19, SIZE_OF_FIXED_STRING_DOESNT_MATCH) \
    M(20, NUMBER_OF_COLUMNS_DOESNT_MATCH) \
    M(21, CANNOT_READ_ALL_DATA_FROM_TAB_SEPARATED_INPUT) \
    M(22, CANNOT_PARSE_ALL_VALUE_FROM_TAB_SEPARATED_INPUT) \
    M(23, CANNOT_READ_FROM_ISTREAM) \
    M(24, CANNOT_WRITE_TO_OSTREAM) \
    M(25, CANNOT_PARSE_ESCAPE_SEQUENCE) \
    M(26, CANNOT_PARSE_QUOTED_STRING) \
    M(27, CANNOT_PARSE_INPUT_ASSERTION_FAILED) \
    M(28, CANNOT_PRINT_FLOAT_OR_DOUBLE_NUMBER) \
    M(29, CANNOT_PRINT_INTEGER) \
    M(30, CANNOT_READ_SIZE_OF_COMPRESSED_CHUNK) \
    M(31, CANNOT_READ_COMPRESSED_CHUNK) \
    M(32, ATTEMPT_TO_READ_AFTER_EOF) \
    M(33, CANNOT_READ_ALL_DATA) \
    M(34, TOO_MANY_ARGUMENTS_FOR_FUNCTION) \
    M(35, TOO_FEW_ARGUMENTS_FOR_FUNCTION) \
    M(36, BAD_ARGUMENTS) \
    M(37, UNKNOWN_ELEMENT_IN_AST) \
    M(38, CANNOT_PARSE_DATE) \
    M(39, TOO_LARGE_SIZE_COMPRESSED) \
    M(40, CHECKSUM_DOESNT_MATCH) \
    M(41, CANNOT_PARSE_DATETIME) \
    M(42, NUMBER_OF_ARGUMENTS_DOESNT_MATCH) \
    M(43, ILLEGAL_TYPE_OF_ARGUMENT) \
    M(44, ILLEGAL_COLUMN) \
    M(45, ILLEGAL_NUMBER_OF_RESULT_COLUMNS) \
    M(46, UNKNOWN_FUNCTION) \
    M(47, UNKNOWN_IDENTIFIER) \
    M(48, NOT_IMPLEMENTED) \
    M(49, LOGICAL_ERROR) \
    M(50, UNKNOWN_TYPE) \
    M(51, EMPTY_LIST_OF_COLUMNS_QUERIED) \
    M(52, COLUMN_QUERIED_MORE_THAN_ONCE) \
    M(53, TYPE_MISMATCH) \
    M(54, STORAGE_DOESNT_ALLOW_PARAMETERS) \
    M(55, STORAGE_REQUIRES_PARAMETER) \
    M(56, UNKNOWN_STORAGE) \
    M(57, TABLE_ALREADY_EXISTS) \
    M(58, TABLE_METADATA_ALREADY_EXISTS) \
    M(59, ILLEGAL_TYPE_OF_COLUMN_FOR_FILTER) \
    M(60, UNKNOWN_TABLE) \
    M(61, ONLY_FILTER_COLUMN_IN_BLOCK) \
    M(62, SYNTAX_ERROR) \
    M(63, UNKNOWN_AGGREGATE_FUNCTION) \
    M(64, CANNOT_READ_AGGREGATE_FUNCTION_FROM_TEXT) \
    M(65, CANNOT_WRITE_AGGREGATE_FUNCTION_AS_TEXT) \
    M(66, NOT_A_COLUMN) \
    M(67, ILLEGAL_KEY_OF_AGGREGATION) \
    M(68, CANNOT_GET_SIZE_OF_FIELD) \
    M(69, ARGUMENT_OUT_OF_BOUND) \
    M(70, CANNOT_CONVERT_TYPE) \
    M(71, CANNOT_WRITE_AFTER_END_OF_BUFFER) \
    M(72, CANNOT_PARSE_NUMBER) \
    M(73, UNKNOWN_FORMAT) \
    M(74, CANNOT_READ_FROM_FILE_DESCRIPTOR) \
    M(75, CANNOT_WRITE_TO_FILE_DESCRIPTOR) \
    M(76, CANNOT_OPEN_FILE) \
    M(77, CANNOT_CLOSE_FILE) \
    M(78, UNKNOWN_TYPE_OF_QUERY) \
    M(79, INCORRECT_FILE_NAME) \
    M(80, INCORRECT_QUERY) \
    M(81, UNKNOWN_DATABASE) \
    M(82, DATABASE_ALREADY_EXISTS) \
    M(83, DIRECTORY_DOESNT_EXIST) \
    M(84, DIRECTORY_ALREADY_EXISTS) \
    M(85, FORMAT_IS_NOT_SUITABLE_FOR_INPUT) \
    M(86, RECEIVED_ERROR_FROM_REMOTE_IO_SERVER) \
    M(87, CANNOT_SEEK_THROUGH_FILE) \
    M(88, CANNOT_TRUNCATE_FILE) \
    M(89, UNKNOWN_COMPRESSION_METHOD) \
    M(90, EMPTY_LIST_OF_COLUMNS_PASSED) \
    M(91, SIZES_OF_MARKS_FILES_ARE_INCONSISTENT) \
    M(92, EMPTY_DATA_PASSED) \
    M(93, UNKNOWN_AGGREGATED_DATA_VARIANT) \
    M(94, CANNOT_MERGE_DIFFERENT_AGGREGATED_DATA_VARIANTS) \
    M(95, CANNOT_READ_FROM_SOCKET) \
    M(96, CANNOT_WRITE_TO_SOCKET) \
    M(97, CANNOT_READ_ALL_DATA_FROM_CHUNKED_INPUT) \
    M(98, CANNOT_WRITE_TO_EMPTY_BLOCK_OUTPUT_STREAM) \
    M(99, UNKNOWN_PACKET_FROM_CLIENT) \
    M(100, UNKNOWN_PACKET_FROM_SERVER) \
    M(101, UNEXPECTED_PACKET_FROM_CLIENT) \
    M(102, UNEXPECTED_PACKET_FROM_SERVER) \
    M(103, RECEIVED_DATA_FOR_WRONG_QUERY_ID) \
    M(104, TOO_SMALL_BUFFER_SIZE) \
    M(105, CANNOT_READ_HISTORY) \
    M(106, CANNOT_APPEND_HISTORY) \
    M(107, FILE_DOESNT_EXIST) \
    M(108, NO_DATA_TO_INSERT) \
    M(109, CANNOT_BLOCK_SIGNAL) \
    M(110, CANNOT_UNBLOCK_SIGNAL) \
    M(111, CANNOT_MANIPULATE_SIGSET) \
    M(112, CANNOT_WAIT_FOR_SIGNAL) \
    M(113, THERE_IS_NO_SESSION) \
    M(114, CANNOT_CLOCK_GETTIME) \
    M(115, UNKNOWN_SETTING) \
    M(116, THERE_IS_NO_DEFAULT_VALUE) \
    M(117, INCORRECT_DATA) \
    M(119, ENGINE_REQUIRED) \
    M(120, CANNOT_INSERT_VALUE_OF_DIFFERENT_SIZE_INTO_TUPLE) \
    M(121, UNSUPPORTED_JOIN_KEYS) \
    M(122, INCOMPATIBLE_COLUMNS) \
    M(123, UNKNOWN_TYPE_OF_AST_NODE) \
    M(124, INCORRECT_ELEMENT_OF_SET) \
    M(125, INCORRECT_RESULT_OF_SCALAR_SUBQUERY) \
    M(126, CANNOT_GET_RETURN_TYPE) \
    M(127, ILLEGAL_INDEX) \
    M(128, TOO_LARGE_ARRAY_SIZE) \
    M(129, FUNCTION_IS_SPECIAL) \
    M(130, CANNOT_READ_ARRAY_FROM_TEXT) \
    M(131, TOO_LARGE_STRING_SIZE) \
    M(133, AGGREGATE_FUNCTION_DOESNT_ALLOW_PARAMETERS) \
    M(134, PARAMETERS_TO_AGGREGATE_FUNCTIONS_MUST_BE_LITERALS) \
    M(135, ZERO_ARRAY_OR_TUPLE_INDEX) \
    M(137, UNKNOWN_ELEMENT_IN_CONFIG) \
    M(138, EXCESSIVE_ELEMENT_IN_CONFIG) \
    M(139, NO_ELEMENTS_IN_CONFIG) \
    M(140, ALL_REQUESTED_COLUMNS_ARE_MISSING) \
    M(141, SAMPLING_NOT_SUPPORTED) \
    M(142, NOT_FOUND_NODE) \
    M(143, FOUND_MORE_THAN_ONE_NODE) \
    M(144, FIRST_DATE_IS_BIGGER_THAN_LAST_DATE) \
    M(145, UNKNOWN_OVERFLOW_MODE) \
    M(146, QUERY_SECTION_DOESNT_MAKE_SENSE) \
    M(147, NOT_FOUND_FUNCTION_ELEMENT_FOR_AGGREGATE) \
    M(148, NOT_FOUND_RELATION_ELEMENT_FOR_CONDITION) \
    M(149, NOT_FOUND_RHS_ELEMENT_FOR_CONDITION) \
    M(150, EMPTY_LIST_OF_ATTRIBUTES_PASSED) \
    M(151, INDEX_OF_COLUMN_IN_SORT_CLAUSE_IS_OUT_OF_RANGE) \
    M(152, UNKNOWN_DIRECTION_OF_SORTING) \
    M(153, ILLEGAL_DIVISION) \
    M(154, AGGREGATE_FUNCTION_NOT_APPLICABLE) \
    M(155, UNKNOWN_RELATION) \
    M(156, DICTIONARIES_WAS_NOT_LOADED) \
    M(157, ILLEGAL_OVERFLOW_MODE) \
    M(158, TOO_MANY_ROWS) \
    M(159, TIMEOUT_EXCEEDED) \
    M(160, TOO_SLOW) \
    M(161, TOO_MANY_COLUMNS) \
    M(162, TOO_DEEP_SUBQUERIES) \
    M(163, TOO_DEEP_PIPELINE) \
    M(164, READONLY) \
    M(165, TOO_MANY_TEMPORARY_COLUMNS) \
    M(166, TOO_MANY_TEMPORARY_NON_CONST_COLUMNS) \
    M(167, TOO_DEEP_AST) \
    M(168, TOO_BIG_AST) \
    M(169, BAD_TYPE_OF_FIELD) \
    M(170, BAD_GET) \
    M(172, CANNOT_CREATE_DIRECTORY) \
    M(173, CANNOT_ALLOCATE_MEMORY) \
    M(174, CYCLIC_ALIASES) \
    M(176, CHUNK_NOT_FOUND) \
    M(177, DUPLICATE_CHUNK_NAME) \
    M(178, MULTIPLE_ALIASES_FOR_EXPRESSION) \
    M(179, MULTIPLE_EXPRESSIONS_FOR_ALIAS) \
    M(180, THERE_IS_NO_PROFILE) \
    M(181, ILLEGAL_FINAL) \
    M(182, ILLEGAL_PREWHERE) \
    M(183, UNEXPECTED_EXPRESSION) \
    M(184, ILLEGAL_AGGREGATION) \
    M(185, UNSUPPORTED_MYISAM_BLOCK_TYPE) \
    M(186, UNSUPPORTED_COLLATION_LOCALE) \
    M(187, COLLATION_COMPARISON_FAILED) \
    M(188, UNKNOWN_ACTION) \
    M(189, TABLE_MUST_NOT_BE_CREATED_MANUALLY) \
    M(190, SIZES_OF_ARRAYS_DOESNT_MATCH) \
    M(191, SET_SIZE_LIMIT_EXCEEDED) \
    M(192, UNKNOWN_USER) \
    M(193, WRONG_PASSWORD) \
    M(194, REQUIRED_PASSWORD) \
    M(195, IP_ADDRESS_NOT_ALLOWED) \
    M(196, UNKNOWN_ADDRESS_PATTERN_TYPE) \
    M(197, SERVER_REVISION_IS_TOO_OLD) \
    M(198, DNS_ERROR) \
    M(199, UNKNOWN_QUOTA) \
    M(200, QUOTA_DOESNT_ALLOW_KEYS) \
    M(201, QUOTA_EXPIRED) \
    M(202, TOO_MANY_SIMULTANEOUS_QUERIES) \
    M(203, NO_FREE_CONNECTION) \
    M(204, CANNOT_FSYNC) \
    M(205, NESTED_TYPE_TOO_DEEP) \
    M(206, ALIAS_REQUIRED) \
    M(207, AMBIGUOUS_IDENTIFIER) \
    M(208, EMPTY_NESTED_TABLE) \
    M(209, SOCKET_TIMEOUT) \
    M(210, NETWORK_ERROR) \
    M(211, EMPTY_QUERY) \
    M(212, UNKNOWN_LOAD_BALANCING) \
    M(213, UNKNOWN_TOTALS_MODE) \
    M(214, CANNOT_STATVFS) \
    M(215, NOT_AN_AGGREGATE) \
    M(216, QUERY_WITH_SAME_ID_IS_ALREADY_RUNNING) \
    M(217, CLIENT_HAS_CONNECTED_TO_WRONG_PORT) \
    M(218, TABLE_IS_DROPPED) \
    M(219, DATABASE_NOT_EMPTY) \
    M(220, DUPLICATE_INTERSERVER_IO_ENDPOINT) \
    M(221, NO_SUCH_INTERSERVER_IO_ENDPOINT) \
    M(222, ADDING_REPLICA_TO_NON_EMPTY_TABLE) \
    M(223, UNEXPECTED_AST_STRUCTURE) \
    M(224, REPLICA_IS_ALREADY_ACTIVE) \
    M(225, NO_ZOOKEEPER) \
    M(226, NO_FILE_IN_DATA_PART) \
    M(227, UNEXPECTED_FILE_IN_DATA_PART) \
    M(228, BAD_SIZE_OF_FILE_IN_DATA_PART) \
    M(229, QUERY_IS_TOO_LARGE) \
    M(230, NOT_FOUND_EXPECTED_DATA_PART) \
    M(231, TOO_MANY_UNEXPECTED_DATA_PARTS) \
    M(232, NO_SUCH_DATA_PART) \
    M(233, BAD_DATA_PART_NAME) \
    M(234, NO_REPLICA_HAS_PART) \
    M(235, DUPLICATE_DATA_PART) \
    M(236, ABORTED) \
    M(237, NO_REPLICA_NAME_GIVEN) \
    M(238, FORMAT_VERSION_TOO_OLD) \
    M(239, CANNOT_MUNMAP) \
    M(240, CANNOT_MREMAP) \
    M(241, MEMORY_LIMIT_EXCEEDED) \
    M(242, TABLE_IS_READ_ONLY) \
    M(243, NOT_ENOUGH_SPACE) \
    M(244, UNEXPECTED_ZOOKEEPER_ERROR) \
    M(246, CORRUPTED_DATA) \
    M(247, INCORRECT_MARK) \
    M(248, INVALID_PARTITION_VALUE) \
    M(250, NOT_ENOUGH_BLOCK_NUMBERS) \
    M(251, NO_SUCH_REPLICA) \
    M(252, TOO_MANY_PARTS) \
    M(253, REPLICA_IS_ALREADY_EXIST) \
    M(254, NO_ACTIVE_REPLICAS) \
    M(255, TOO_MANY_RETRIES_TO_FETCH_PARTS) \
    M(256, PARTITION_ALREADY_EXISTS) \
    M(257, PARTITION_DOESNT_EXIST) \
    M(258, UNION_ALL_RESULT_STRUCTURES_MISMATCH) \
    M(260, CLIENT_OUTPUT_FORMAT_SPECIFIED) \
    M(261, UNKNOWN_BLOCK_INFO_FIELD) \
    M(262, BAD_COLLATION) \
    M(263, CANNOT_COMPILE_CODE) \
    M(264, INCOMPATIBLE_TYPE_OF_JOIN) \
    M(265, NO_AVAILABLE_REPLICA) \
    M(266, MISMATCH_REPLICAS_DATA_SOURCES) \
    M(267, STORAGE_DOESNT_SUPPORT_PARALLEL_REPLICAS) \
    M(268, CPUID_ERROR) \
    M(269, INFINITE_LOOP) \
    M(270, CANNOT_COMPRESS) \
    M(271, CANNOT_DECOMPRESS) \
    M(272, CANNOT_IO_SUBMIT) \
    M(273, CANNOT_IO_GETEVENTS) \
    M(274, AIO_READ_ERROR) \
    M(275, AIO_WRITE_ERROR) \
    M(277, INDEX_NOT_USED) \
    M(279, ALL_CONNECTION_TRIES_FAILED) \
    M(280, NO_AVAILABLE_DATA) \
    M(281, DICTIONARY_IS_EMPTY) \
    M(282, INCORRECT_INDEX) \
    M(283, UNKNOWN_DISTRIBUTED_PRODUCT_MODE) \
    M(284, WRONG_GLOBAL_SUBQUERY) \
    M(285, TOO_FEW_LIVE_REPLICAS) \
    M(286, UNSATISFIED_QUORUM_FOR_PREVIOUS_WRITE) \
    M(287, UNKNOWN_FORMAT_VERSION) \
    M(288, DISTRIBUTED_IN_JOIN_SUBQUERY_DENIED) \
    M(289, REPLICA_IS_NOT_IN_QUORUM) \
    M(290, LIMIT_EXCEEDED) \
    M(291, DATABASE_ACCESS_DENIED) \
    M(293, MONGODB_CANNOT_AUTHENTICATE) \
    M(294, INVALID_BLOCK_EXTRA_INFO) \
    M(295, RECEIVED_EMPTY_DATA) \
    M(296, NO_REMOTE_SHARD_FOUND) \
    M(297, SHARD_HAS_NO_CONNECTIONS) \
    M(298, CANNOT_PIPE) \
    M(299, CANNOT_FORK) \
    M(300, CANNOT_DLSYM) \
    M(301, CANNOT_CREATE_CHILD_PROCESS) \
    M(302, CHILD_WAS_NOT_EXITED_NORMALLY) \
    M(303, CANNOT_SELECT) \
    M(304, CANNOT_WAITPID) \
    M(305, TABLE_WAS_NOT_DROPPED) \
    M(306, TOO_DEEP_RECURSION) \
    M(307, TOO_MANY_BYTES) \
    M(308, UNEXPECTED_NODE_IN_ZOOKEEPER) \
    M(309, FUNCTION_CANNOT_HAVE_PARAMETERS) \
    M(317, INVALID_SHARD_WEIGHT) \
    M(318, INVALID_CONFIG_PARAMETER) \
    M(319, UNKNOWN_STATUS_OF_INSERT) \
    M(321, VALUE_IS_OUT_OF_RANGE_OF_DATA_TYPE) \
    M(335, BARRIER_TIMEOUT) \
    M(336, UNKNOWN_DATABASE_ENGINE) \
    M(337, DDL_GUARD_IS_ACTIVE) \
    M(341, UNFINISHED) \
    M(342, METADATA_MISMATCH) \
    M(344, SUPPORT_IS_DISABLED) \
    M(345, TABLE_DIFFERS_TOO_MUCH) \
    M(346, CANNOT_CONVERT_CHARSET) \
    M(347, CANNOT_LOAD_CONFIG) \
    M(349, CANNOT_INSERT_NULL_IN_ORDINARY_COLUMN) \
    M(350, INCOMPATIBLE_SOURCE_TABLES) \
    M(351, AMBIGUOUS_TABLE_NAME) \
    M(352, AMBIGUOUS_COLUMN_NAME) \
    M(353, INDEX_OF_POSITIONAL_ARGUMENT_IS_OUT_OF_RANGE) \
    M(354, ZLIB_INFLATE_FAILED) \
    M(355, ZLIB_DEFLATE_FAILED) \
    M(356, BAD_LAMBDA) \
    M(357, RESERVED_IDENTIFIER_NAME) \
    M(358, INTO_OUTFILE_NOT_ALLOWED) \
    M(359, TABLE_SIZE_EXCEEDS_MAX_DROP_SIZE_LIMIT) \
    M(360, CANNOT_CREATE_CHARSET_CONVERTER) \
    M(361, SEEK_POSITION_OUT_OF_BOUND) \
    M(362, CURRENT_WRITE_BUFFER_IS_EXHAUSTED) \
    M(363, CANNOT_CREATE_IO_BUFFER) \
    M(364, RECEIVED_ERROR_TOO_MANY_REQUESTS) \
    M(366, SIZES_OF_NESTED_COLUMNS_ARE_INCONSISTENT) \
    M(367, TOO_MANY_FETCHES) \
    M(369, ALL_REPLICAS_ARE_STALE) \
    M(370, DATA_TYPE_CANNOT_BE_USED_IN_TABLES) \
    M(371, INCONSISTENT_CLUSTER_DEFINITION) \
    M(372, SESSION_NOT_FOUND) \
    M(373, SESSION_IS_LOCKED) \
    M(374, INVALID_SESSION_TIMEOUT) \
    M(375, CANNOT_DLOPEN) \
    M(376, CANNOT_PARSE_UUID) \
    M(377, ILLEGAL_SYNTAX_FOR_DATA_TYPE) \
    M(378, DATA_TYPE_CANNOT_HAVE_ARGUMENTS) \
    M(379, UNKNOWN_STATUS_OF_DISTRIBUTED_DDL_TASK) \
    M(380, CANNOT_KILL) \
    M(381, HTTP_LENGTH_REQUIRED) \
    M(382, CANNOT_LOAD_CATBOOST_MODEL) \
    M(383, CANNOT_APPLY_CATBOOST_MODEL) \
    M(384, PART_IS_TEMPORARILY_LOCKED) \
    M(385, MULTIPLE_STREAMS_REQUIRED) \
    M(386, NO_COMMON_TYPE) \
    M(387, DICTIONARY_ALREADY_EXISTS) \
    M(388, CANNOT_ASSIGN_OPTIMIZE) \
    M(389, INSERT_WAS_DEDUPLICATED) \
    M(390, CANNOT_GET_CREATE_TABLE_QUERY) \
    M(391, EXTERNAL_LIBRARY_ERROR) \
    M(392, QUERY_IS_PROHIBITED) \
    M(393, THERE_IS_NO_QUERY) \
    M(394, QUERY_WAS_CANCELLED) \
    M(395, FUNCTION_THROW_IF_VALUE_IS_NON_ZERO) \
    M(396, TOO_MANY_ROWS_OR_BYTES) \
    M(397, QUERY_IS_NOT_SUPPORTED_IN_MATERIALIZED_VIEW) \
    M(398, UNKNOWN_MUTATION_COMMAND) \
    M(399, FORMAT_IS_NOT_SUITABLE_FOR_OUTPUT) \
    M(400, CANNOT_STAT) \
    M(401, FEATURE_IS_NOT_ENABLED_AT_BUILD_TIME) \
    M(402, CANNOT_IOSETUP) \
    M(403, INVALID_JOIN_ON_EXPRESSION) \
    M(404, BAD_ODBC_CONNECTION_STRING) \
    M(405, PARTITION_SIZE_EXCEEDS_MAX_DROP_SIZE_LIMIT) \
    M(406, TOP_AND_LIMIT_TOGETHER) \
    M(407, DECIMAL_OVERFLOW) \
    M(408, BAD_REQUEST_PARAMETER) \
    M(409, EXTERNAL_EXECUTABLE_NOT_FOUND) \
    M(410, EXTERNAL_SERVER_IS_NOT_RESPONDING) \
    M(411, PTHREAD_ERROR) \
    M(412, NETLINK_ERROR) \
    M(413, CANNOT_SET_SIGNAL_HANDLER) \
    M(415, ALL_REPLICAS_LOST) \
    M(416, REPLICA_STATUS_CHANGED) \
    M(417, EXPECTED_ALL_OR_ANY) \
    M(418, UNKNOWN_JOIN) \
    M(419, MULTIPLE_ASSIGNMENTS_TO_COLUMN) \
    M(420, CANNOT_UPDATE_COLUMN) \
    M(421, CANNOT_ADD_DIFFERENT_AGGREGATE_STATES) \
    M(422, UNSUPPORTED_URI_SCHEME) \
    M(423, CANNOT_GETTIMEOFDAY) \
    M(424, CANNOT_LINK) \
    M(425, SYSTEM_ERROR) \
    M(427, CANNOT_COMPILE_REGEXP) \
    M(428, UNKNOWN_LOG_LEVEL) \
    M(429, FAILED_TO_GETPWUID) \
    M(430, MISMATCHING_USERS_FOR_PROCESS_AND_DATA) \
    M(431, ILLEGAL_SYNTAX_FOR_CODEC_TYPE) \
    M(432, UNKNOWN_CODEC) \
    M(433, ILLEGAL_CODEC_PARAMETER) \
    M(434, CANNOT_PARSE_PROTOBUF_SCHEMA) \
    M(435, NO_COLUMN_SERIALIZED_TO_REQUIRED_PROTOBUF_FIELD) \
    M(436, PROTOBUF_BAD_CAST) \
    M(437, PROTOBUF_FIELD_NOT_REPEATED) \
    M(438, DATA_TYPE_CANNOT_BE_PROMOTED) \
    M(439, CANNOT_SCHEDULE_TASK) \
    M(440, INVALID_LIMIT_EXPRESSION) \
    M(441, CANNOT_PARSE_DOMAIN_VALUE_FROM_STRING) \
    M(442, BAD_DATABASE_FOR_TEMPORARY_TABLE) \
    M(443, NO_COLUMNS_SERIALIZED_TO_PROTOBUF_FIELDS) \
    M(444, UNKNOWN_PROTOBUF_FORMAT) \
    M(445, CANNOT_MPROTECT) \
    M(446, FUNCTION_NOT_ALLOWED) \
    M(447, HYPERSCAN_CANNOT_SCAN_TEXT) \
    M(448, BROTLI_READ_FAILED) \
    M(449, BROTLI_WRITE_FAILED) \
    M(450, BAD_TTL_EXPRESSION) \
    M(451, BAD_TTL_FILE) \
    M(452, SETTING_CONSTRAINT_VIOLATION) \
    M(453, MYSQL_CLIENT_INSUFFICIENT_CAPABILITIES) \
    M(454, OPENSSL_ERROR) \
    M(455, SUSPICIOUS_TYPE_FOR_LOW_CARDINALITY) \
    M(456, UNKNOWN_QUERY_PARAMETER) \
    M(457, BAD_QUERY_PARAMETER) \
    M(458, CANNOT_UNLINK) \
    M(459, CANNOT_SET_THREAD_PRIORITY) \
    M(460, CANNOT_CREATE_TIMER) \
    M(461, CANNOT_SET_TIMER_PERIOD) \
    M(462, CANNOT_DELETE_TIMER) \
    M(463, CANNOT_FCNTL) \
    M(464, CANNOT_PARSE_ELF) \
    M(465, CANNOT_PARSE_DWARF) \
    M(466, INSECURE_PATH) \
    M(467, CANNOT_PARSE_BOOL) \
    M(468, CANNOT_PTHREAD_ATTR) \
    M(469, VIOLATED_CONSTRAINT) \
    M(470, QUERY_IS_NOT_SUPPORTED_IN_LIVE_VIEW) \
    M(471, INVALID_SETTING_VALUE) \
    M(472, READONLY_SETTING) \
    M(473, DEADLOCK_AVOIDED) \
    M(474, INVALID_TEMPLATE_FORMAT) \
    M(475, INVALID_WITH_FILL_EXPRESSION) \
    M(476, WITH_TIES_WITHOUT_ORDER_BY) \
    M(477, INVALID_USAGE_OF_INPUT) \
    M(478, UNKNOWN_POLICY) \
    M(479, UNKNOWN_DISK) \
    M(480, UNKNOWN_PROTOCOL) \
    M(481, PATH_ACCESS_DENIED) \
    M(482, DICTIONARY_ACCESS_DENIED) \
    M(483, TOO_MANY_REDIRECTS) \
    M(484, INTERNAL_REDIS_ERROR) \
    M(485, SCALAR_ALREADY_EXISTS) \
    M(487, CANNOT_GET_CREATE_DICTIONARY_QUERY) \
    M(488, UNKNOWN_DICTIONARY) \
    M(489, INCORRECT_DICTIONARY_DEFINITION) \
    M(490, CANNOT_FORMAT_DATETIME) \
    M(491, UNACCEPTABLE_URL) \
    M(492, ACCESS_ENTITY_NOT_FOUND) \
    M(493, ACCESS_ENTITY_ALREADY_EXISTS) \
    M(494, ACCESS_ENTITY_FOUND_DUPLICATES) \
    M(495, ACCESS_STORAGE_READONLY) \
    M(496, QUOTA_REQUIRES_CLIENT_KEY) \
    M(497, ACCESS_DENIED) \
    M(498, LIMIT_BY_WITH_TIES_IS_NOT_SUPPORTED) \
    M(499, S3_ERROR) \
    M(501, CANNOT_CREATE_DATABASE) \
    M(502, CANNOT_SIGQUEUE) \
    M(503, AGGREGATE_FUNCTION_THROW) \
    M(504, FILE_ALREADY_EXISTS) \
    M(505, CANNOT_DELETE_DIRECTORY) \
    M(506, UNEXPECTED_ERROR_CODE) \
    M(507, UNABLE_TO_SKIP_UNUSED_SHARDS) \
    M(508, UNKNOWN_ACCESS_TYPE) \
    M(509, INVALID_GRANT) \
    M(510, CACHE_DICTIONARY_UPDATE_FAIL) \
    M(511, UNKNOWN_ROLE) \
    M(512, SET_NON_GRANTED_ROLE) \
    M(513, UNKNOWN_PART_TYPE) \
    M(514, ACCESS_STORAGE_FOR_INSERTION_NOT_FOUND) \
    M(515, INCORRECT_ACCESS_ENTITY_DEFINITION) \
    M(516, AUTHENTICATION_FAILED) \
    M(517, CANNOT_ASSIGN_ALTER) \
    M(518, CANNOT_COMMIT_OFFSET) \
    M(519, NO_REMOTE_SHARD_AVAILABLE) \
    M(520, CANNOT_DETACH_DICTIONARY_AS_TABLE) \
    M(521, ATOMIC_RENAME_FAIL) \
    M(523, UNKNOWN_ROW_POLICY) \
    M(524, ALTER_OF_COLUMN_IS_FORBIDDEN) \
    M(525, INCORRECT_DISK_INDEX) \
    M(526, UNKNOWN_VOLUME_TYPE) \
    M(527, NO_SUITABLE_FUNCTION_IMPLEMENTATION) \
    M(528, CASSANDRA_INTERNAL_ERROR) \
    M(529, NOT_A_LEADER) \
    M(530, CANNOT_CONNECT_RABBITMQ) \
    M(531, CANNOT_FSTAT) \
    M(532, LDAP_ERROR) \
    M(533, INCONSISTENT_RESERVATIONS) \
    M(534, NO_RESERVATIONS_PROVIDED) \
    M(535, UNKNOWN_RAID_TYPE) \
    M(536, CANNOT_RESTORE_FROM_FIELD_DUMP) \
    M(537, ILLEGAL_MYSQL_VARIABLE) \
    M(538, MYSQL_SYNTAX_ERROR) \
    M(539, CANNOT_BIND_RABBITMQ_EXCHANGE) \
    M(540, CANNOT_DECLARE_RABBITMQ_EXCHANGE) \
    M(541, CANNOT_CREATE_RABBITMQ_QUEUE_BINDING) \
    M(542, CANNOT_REMOVE_RABBITMQ_EXCHANGE) \
    M(543, UNKNOWN_MYSQL_DATATYPES_SUPPORT_LEVEL) \
    M(544, ROW_AND_ROWS_TOGETHER) \
    M(545, FIRST_AND_NEXT_TOGETHER) \
    M(546, NO_ROW_DELIMITER) \
    M(547, INVALID_RAID_TYPE) \
    M(548, UNKNOWN_VOLUME) \
    M(549, DATA_TYPE_CANNOT_BE_USED_IN_KEY) \
    M(550, CONDITIONAL_TREE_PARENT_NOT_FOUND) \
    M(551, ILLEGAL_PROJECTION_MANIPULATOR) \
    M(552, UNRECOGNIZED_ARGUMENTS) \
    M(553, LZMA_STREAM_ENCODER_FAILED) \
    M(554, LZMA_STREAM_DECODER_FAILED) \
    M(555, ROCKSDB_ERROR) \
    M(556, SYNC_MYSQL_USER_ACCESS_ERROR)\
    M(557, UNKNOWN_UNION) \
    M(558, EXPECTED_ALL_OR_DISTINCT) \
    M(559, INVALID_GRPC_QUERY_INFO) \
    M(560, ZSTD_ENCODER_FAILED) \
    M(561, ZSTD_DECODER_FAILED) \
    M(562, TLD_LIST_NOT_FOUND) \
    M(563, CANNOT_READ_MAP_FROM_TEXT) \
    M(564, INTERSERVER_SCHEME_DOESNT_MATCH) \
    M(565, TOO_MANY_PARTITIONS) \
    M(566, CANNOT_RMDIR) \
    M(567, DUPLICATED_PART_UUIDS) \
    M(568, RAFT_ERROR) \
    M(569, MULTIPLE_COLUMNS_SERIALIZED_TO_SAME_PROTOBUF_FIELD) \
    M(570, DATA_TYPE_INCOMPATIBLE_WITH_PROTOBUF_FIELD) \
    M(571, DATABASE_REPLICATION_FAILED) \
    M(572, TOO_MANY_QUERY_PLAN_OPTIMIZATIONS) \
    M(573, EPOLL_ERROR) \
    M(574, DISTRIBUTED_TOO_MANY_PENDING_BYTES) \
    M(575, UNKNOWN_SNAPSHOT) \
    M(576, KERBEROS_ERROR) \
    M(577, INVALID_SHARD_ID) \
    M(578, INVALID_FORMAT_INSERT_QUERY_WITH_DATA) \
    M(579, INCORRECT_PART_TYPE) \
    M(580, CANNOT_SET_ROUNDING_MODE) \
    M(581, TOO_LARGE_DISTRIBUTED_DEPTH) \
    M(582, NO_SUCH_PROJECTION_IN_TABLE) \
    M(583, ILLEGAL_PROJECTION) \
    M(584, PROJECTION_NOT_USED) \
    M(585, CANNOT_PARSE_YAML) \
    M(586, CANNOT_CREATE_FILE) \
    M(587, CONCURRENT_ACCESS_NOT_SUPPORTED) \
    M(588, DISTRIBUTED_BROKEN_BATCH_INFO) \
    M(589, DISTRIBUTED_BROKEN_BATCH_FILES) \
    M(590, CANNOT_SYSCONF) \
    M(591, SQLITE_ENGINE_ERROR) \
    M(592, DATA_ENCRYPTION_ERROR) \
    M(593, ZERO_COPY_REPLICATION_ERROR) \
    M(594, BZIP2_STREAM_DECODER_FAILED) \
    M(595, BZIP2_STREAM_ENCODER_FAILED) \
    M(596, INTERSECT_OR_EXCEPT_RESULT_STRUCTURES_MISMATCH) \
    M(597, CANNOT_ADVISE) \
    \
    M(998, POSTGRESQL_CONNECTION_FAILURE) \
    M(999, KEEPER_EXCEPTION) \
    M(1000, POCO_EXCEPTION) \
    M(1001, STD_EXCEPTION) \
    M(1002, UNKNOWN_EXCEPTION) \

/* See END */

namespace DB
{
namespace ErrorCodes
{
#define M(VALUE, NAME) extern const ErrorCode NAME = VALUE;
    APPLY_FOR_ERROR_CODES(M)
#undef M

    constexpr ErrorCode END = 3000;
    ErrorPairHolder values[END + 1]{};

    struct ErrorCodesNames
    {
        std::string_view names[END + 1];
        ErrorCodesNames()
        {
#define M(VALUE, NAME) names[VALUE] = std::string_view(#NAME);
            APPLY_FOR_ERROR_CODES(M)
#undef M
        }
    } error_codes_names;

    std::string_view getName(ErrorCode error_code)
    {
        if (error_code < 0 || error_code >= END)
            return std::string_view();
        return error_codes_names.names[error_code];
    }

    ErrorCode end() { return END + 1; }

    void increment(ErrorCode error_code, bool remote, const std::string & message, const FramePointers & trace)
    {
        if (error_code < 0 || error_code >= end())
        {
            /// For everything outside the range, use END.
            /// (end() is the pointer pass the end, while END is the last value that has an element in values array).
            error_code = end() - 1;
        }

        values[error_code].increment(remote, message, trace);
    }

    void ErrorPairHolder::increment(bool remote, const std::string & message, const FramePointers & trace)
    {
        const auto now = std::chrono::system_clock::now();

        std::lock_guard lock(mutex);

        auto & error = remote ? value.remote : value.local;

        ++error.count;
        error.message = message;
        error.trace = trace;
        error.error_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    }
    ErrorPair ErrorPairHolder::get()
    {
        std::lock_guard lock(mutex);
        return value;
    }
}

}
