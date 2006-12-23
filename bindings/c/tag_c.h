/***************************************************************************
    copyright            : (C) 2003 by Scott Wheeler
    email                : wheeler@kde.org
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 ***************************************************************************/

#ifndef TAGLIB_TAG_C
#define TAGLIB_TAG_C

/* Do not include this in the main TagLib documentation. */
#ifndef DO_NOT_DOCUMENT

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BOOL
#define BOOL int
#endif

/*******************************************************************************
 * [ TagLib C Binding ]
 *
 * This is an interface to TagLib's "simple" API, meaning that you can read and
 * modify media files in a generic, but not specialized way.  This is a rough
 * representation of TagLib::File and TagLib::Tag, for which the documentation
 * is somewhat more complete and worth consulting.
 *******************************************************************************/

/*
 * These are used for type provide some type safety to the C API (as opposed to
 * using void *, but pointers to them are simply cast to the coresponding C++
 * types in the implementation.
 */

typedef struct { int dummy; } TagLib_File;
typedef struct { int dummy; } TagLib_Tag;
typedef struct { int dummy; } TagLib_AudioProperties;

/*!
 * By default all strings coming into or out of TagLib's C API are in UTF8.
 * However, it may be desirable for TagLib to operate on Latin1 (ISO-8859-1)
 * strings in which case this should be set to FALSE.
 */
void taglib_set_strings_unicode(BOOL unicode);

/*!
 * TagLib can keep track of strings that are created when outputting tag values
 * and clear them using taglib_tag_clear_strings().  This is enabled by default.
 * However if you wish to do more fine grained management of strings, you can do
 * so by setting \a management to FALSE.
 */
void taglib_set_string_management_enabled(BOOL management);

/*******************************************************************************
 * File API
 ******************************************************************************/

typedef enum {
  TagLib_File_MPEG,
  TagLib_File_OggVorbis,
  TagLib_File_FLAC,
  TagLib_File_MPC,
  TagLib_File_OggFlac
} TagLib_File_Type;

/*!
 * Creates a TagLib file based on \a filename.  TagLib will try to guess the file
 * type.
 * 
 * \returns NULL if the file type cannot be determined or the file cannot
 * be opened.
 */
TagLib_File *taglib_file_new(const char *filename);

/*!
 * Creates a TagLib file based on \a filename.  Rather than attempting to guess
 * the type, it will use the one specified by \a type.
 */
TagLib_File *taglib_file_new_type(const char *filename, TagLib_File_Type type);

/*!
 * Frees and closes the file.
 */
void taglib_file_free(TagLib_File *file);

/*!
 * Returns a pointer to the tag associated with this file.  This will be freed
 * automatically when the file is freed.
 */
TagLib_Tag *taglib_file_tag(const TagLib_File *file);

/*!
 * Returns a pointer to the the audio properties associated with this file.  This
 * will be freed automatically when the file is freed.
 */
const TagLib_AudioProperties *taglib_file_audioproperties(const TagLib_File *file);

/*!
 * Saves the \a file to disk.
 */
BOOL taglib_file_save(TagLib_File *file);

/******************************************************************************
 * Tag API
 ******************************************************************************/

/*!
 * Returns a string with this tag's title.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
char *taglib_tag_title(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's artist.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
char *taglib_tag_artist(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's album name.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
char *taglib_tag_album(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's comment.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
char *taglib_tag_comment(const TagLib_Tag *tag);

/*!
 * Returns a string with this tag's genre.
 *
 * \note By default this string should be UTF8 encoded and its memory should be
 * freed using taglib_tag_free_strings().
 */
char *taglib_tag_genre(const TagLib_Tag *tag);

/*!
 * Returns the tag's year or 0 if year is not set.
 */
unsigned int taglib_tag_year(const TagLib_Tag *tag);

/*!
 * Returns the tag's track number or 0 if track number is not set.
 */
unsigned int taglib_tag_track(const TagLib_Tag *tag);

/*!
 * Sets the tag's title.
 *
 * \note By default this string should be UTF8 encoded.
 */
void taglib_tag_set_title(TagLib_Tag *tag, const char *title);

/*!
 * Sets the tag's artist.
 *
 * \note By default this string should be UTF8 encoded.
 */
void taglib_tag_set_artist(TagLib_Tag *tag, const char *artist);

/*!
 * Sets the tag's album.
 *
 * \note By default this string should be UTF8 encoded.
 */
void taglib_tag_set_album(TagLib_Tag *tag, const char *album);

/*!
 * Sets the tag's comment.
 *
 * \note By default this string should be UTF8 encoded.
 */
void taglib_tag_set_comment(TagLib_Tag *tag, const char *comment);

/*!
 * Sets the tag's genre.
 *
 * \note By default this string should be UTF8 encoded.
 */
void taglib_tag_set_genre(TagLib_Tag *tag, const char *genre);

/*!
 * Sets the tag's year.  0 indicates that this field should be cleared.
 */
void taglib_tag_set_year(TagLib_Tag *tag, unsigned int year);

/*!
 * Sets the tag's track number.  0 indicates that this field should be cleared.
 */
void taglib_tag_set_track(TagLib_Tag *tag, unsigned int track);

/*!
 * Frees all of the strings that have been created by the tag.
 */
void taglib_tag_free_strings();

/******************************************************************************
 * Audio Properties API
 ******************************************************************************/

/*!
 * Returns the lenght of the file in seconds.
 */
int taglib_audioproperties_length(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the bitrate of the file in kb/s.
 */
int taglib_audioproperties_bitrate(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the sample rate of the file in Hz.
 */
int taglib_audioproperties_samplerate(const TagLib_AudioProperties *audioProperties);

/*!
 * Returns the number of channels in the audio stream.
 */
int taglib_audioproperties_channels(const TagLib_AudioProperties *audioProperties);

/*******************************************************************************
 * Special convenience ID3v2 functions
 *******************************************************************************/

typedef enum {
  TagLib_ID3v2_Latin1,
  TagLib_ID3v2_UTF16,
  TagLib_ID3v2_UTF16BE,
  TagLib_ID3v2_UTF8
} TagLib_ID3v2_Encoding;

/*!
 * This sets the default encoding for ID3v2 frames that are written to tags.
 */

void taglib_id3v2_set_default_text_encoding(TagLib_ID3v2_Encoding encoding);

#ifdef __cplusplus
}
#endif
#endif /* DO_NOT_DOCUMENT */
#endif