#ifndef _EDI_EDITOR_H
#define _EDI_EDITOR_H

#if HAVE_LIBCLANG
#include <clang-c/Index.h>
#endif
#include <time.h>

#include <Evas.h>

#include "mainview/edi_mainview_item.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief These routines are used for interacting with the main Edi editor view.
 */

/**
 * @typedef Edi_Editor_Search
 * An instance of an editor search session.
 */
typedef struct _Edi_Editor_Search Edi_Editor_Search;

/**
 * @typedef Edi_Editor
 * An instance of an editor view.
 */
typedef struct _Edi_Editor Edi_Editor;

/**
 * @struct _Edi_Editor
 * An instance of an editor view.
 */
struct _Edi_Editor
{
   Evas_Object *entry; /**< The main text entry widget for the editor */
   Evas_Object *suggest_bg; /**< The autosuggest background */
   Evas_Object *suggest_genlist; /**< The autosuggest genlist */
   Eina_List *undo_stack; /**< The list of operations that can be undone */

   /* Private */
   Edi_Editor_Search *search;
   Eina_Bool modified;
   Ecore_Timer *save_timer;

#if HAVE_LIBCLANG
   /* Clang */
   CXIndex idx;
   CXTranslationUnit tx_unit;
   CXToken *tokens;
   CXCursor *cursors;
   unsigned int token_count;

   CXIndex as_idx;
   CXTranslationUnit as_unit;
#endif

   Eina_Bool show_highlight;
   Ecore_Thread *highlight_thread;
   Eina_Bool highlight_cancel;
   time_t save_time;

   const char *mimetype;

   /* Add new members here. */
};

/**
 * @brief Editor.
 * @defgroup Editor The main text editor functions
 *
 * @{
 *
 */

/**
 * Initialize a new Edi editor and add it to the parent panel.
 *
 * @param parent The panel into which the panel will be loaded.
 * @param item The item describing the file to be loaded in the editor.
 * @return the created evas object that contains the editor.
 *
 * @ingroup Editor
 */
Evas_Object *edi_editor_add(Evas_Object *parent, Edi_Mainview_Item *item);

/**
 * @}
 *
 * @brief Widgets.
 * @defgroup Widget Functions that open or manipulate feature panels
 *
 * @{
 *
 */

/**
 * Add a search widget to the specified editor.
 *
 * @param parent The panel that the UI should be added to,
 * @param editor The Edi_Editor instance that we are searching for text within.
 *
 * @ingroup Widgets
 */
void edi_editor_search_add(Evas_Object *parent, Edi_Editor *editor);

/**
 * Start a search in the specified editor.
 *
 * @param editor the text editor instance to search within.
 *
 * @ingroup Widgets
 */
void edi_editor_search(Edi_Editor *editor);

/**
 * Save the content of the specified editor.
 *
 * @param editor the text editor instance to save.
 *
 * @ingroup Widgets
 */
void edi_editor_save(Edi_Editor *editor);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
