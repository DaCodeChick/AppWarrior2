#pragma once

#include "typedefs.hpp"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	/** @brief Concatenates 2 Pascal strings
	 * @param dst The destination string
	 * @param src The source string
	 * @return The new length of the concatenated string
	*/
	HXAPI int pstrcat(unsigned char *dst, const unsigned char *src);

	/** @brief Compares 2 Pascal strings
	 * 	@return False (0) or true (1)
	 */
	HXAPI int pstrcmp(const unsigned char *str1, const unsigned char *str2);

	/** @brief Copies a Pascal string to a given buffer
	 *  @param dst The destination buffer
	 * 	@param src The source string
	 * 	@return The string length
	 */
	HXAPI int pstrcpy(unsigned char *dst, const unsigned char *src);

	/** @brief Copies a Pascal string to a given buffer up to a given length
	 *  @param dst The destination buffer
	 * 	@param src The source string
	 * 	@param len Total number of bytes to copy
	 * 	@return The string length
	 */
	HXAPI int pstrncpy(unsigned char *dst, const unsigned char *src, int len);

	/** @brief Finds the last occurence of a character in a Pascal string
	 * 	@return Pointer to the character or NULL if absent
	 */
	HXAPI unsigned char * pstrrchr(const unsigned char *str, int c);
#ifdef __cplusplus
}
#endif // __cplusplus
