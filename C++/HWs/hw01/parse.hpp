#ifndef _PARSE_HPP_
#define _PARSE_HPP_

#include <string>
#include <vector>

/**
 * Header file for parsing inputs and printing out the header and lines
 */

/** 
 *  @brief Configuration struct 
 */
typedef struct{
    std::string type;       /**< Type of the config as string  */
    std::string value;      /**< Value after '=' char  */
    bool valid;             /**< true if this configuration is valid  */
}config_t;

/** 
 *  @brief Sum struct
 */
typedef struct{
    int value;              /**< Sum of the cells  */
    bool valid;             /**< true if this sum is valid  */
    int width;              /**< Width of the text  */
}sum_t;

typedef struct {
    int min;
    int max;
    int width;
    std::string align;
    int stretch;
    int header;
} cfg_values_t;

static const std::string MIN_TYPE = "min";

static const std::string MAX_TYPE = "max";

static const std::string WIDTH_TYPE = "width";

static const std::string ALIGN_TYPE = "align";

static const std::string STRETCH_TYPE = "stretch";

static const std::string HEADER_TYPE = "header";

static const std::string CONFIG_PREFIX = "config";

static const std::string CONFIG_PREFIX_DOT = CONFIG_PREFIX + ".";

static const std::string EQUAL_SIGN = "=";

/**
 *  @brief Parse input string to parse input configuration
 * 
 *  @param text Input string for parsing (one line)
 *  @retval Configuration struct (config_t) with parsed values
 * 
 */
config_t getConfig(std::string text);

/** 
 *  @brief Parse sum cell and return value and its validity
 * 
 *  @param text Text for parsing in format SUM(FROM:TO)
 *  @param numbers Vector of numbers which can be summed
 *  @retval sum_t struct with the value, text width and valid information
 * 
 */
sum_t getSum(std::string text, std::vector<int> numbers);

cfg_values_t get_default_cfg_values();

cfg_values_t set_cfg_values(cfg_values_t allCfgValues, const config_t& cfgValue);

void printCfgValue(std::string type, std::string value);

void printCfgValues(cfg_values_t cfgValues);

#endif // __PARSE_HPP_