#ifndef EDI_SCM_H_
# define EDI_SCM_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief These routines are used for Edi SCM management.
 */

typedef int (scm_fn_add)(const char *path);
typedef int (scm_fn_mod)(const char *path);
typedef int (scm_fn_del)(const char *path);
typedef int (scm_fn_credits)(const char *name, const char *email);
typedef int (scm_fn_move)(const char *src, const char *dest);
typedef int (scm_fn_commit)(const char *message);
typedef int (scm_fn_remote_add)(const char *remote_url);
typedef int (scm_fn_status)(void);
typedef int (scm_fn_push)(void);
typedef int (scm_fn_pull)(void);
typedef int (scm_fn_stash)(void);

typedef const char * (scm_fn_remote_name)(void);
typedef const char * (scm_fn_remote_email)(void);
typedef const char * (scm_fn_remote_url)(void);

typedef struct _Edi_Scm_Engine
{
   const char     *name;
   const char     *directory;
   const char     *path;

   scm_fn_remote_add *remote_add;
   const char        *remote_url;
   const char        *remote_name;
   const char        *remote_email;

   scm_fn_credits *credits;
   scm_fn_add     *file_add;
   scm_fn_mod     *file_mod;
   scm_fn_del     *file_del;
   scm_fn_move    *move;
   scm_fn_commit  *commit;
   scm_fn_status  *status;
   scm_fn_push    *push;
   scm_fn_pull    *pull;
   scm_fn_stash   *stash;

   scm_fn_remote_name  *_remote_name_get;
   scm_fn_remote_email *_remote_email_get;
   scm_fn_remote_url   *_remote_url_get;
} Edi_Scm_Engine;

/**
 * @brief Executable helpers
 * @defgroup Scm
 *
 * @{
 *
 * Functions of source code management.
 *
 */

/**
 * Init the SCM system for the current project.
 *
 * @ingroup Scm
 */
Edi_Scm_Engine *edi_scm_init();

/**
 * Shutdown and free memory in use by SCM system.
 *
 * @ingroup Scm
 */
void edi_scm_shutdown();

/**
 * Set up a new git repository for the current project.
 *
 * @ingroup Scm
 */
EAPI int edi_scm_git_new(void);

/**
 * Get a pointer to the SCM engine in use.
 *
 * @return The pointer to the engine or NULL.
 *
 * @ingroup Scm
 */
Edi_Scm_Engine *edi_scm_engine_get(void);

/**
 * Add file to be monitored by SCM.
 *
 * @param path The file path.
 * @return The status code of command executed.
 *
 * @ingroup Scm
 */
int edi_scm_add(const char *path);

/**
 * Del file from those monitored by SCM.
 *
 * @param path The file path.
 * @return The status code of command executed.
 *
 * @ingroup Scm
 */
int edi_scm_del(const char *path);

/**
 * Set commit message for next commit to SCM.
 *
 * @param message The commit mesage to send.
 *
 * @ingroup Scm
 */
void edi_scm_commit(const char *message);

/**
 * Get status of repository.
 *
 * @ingroup Scm
 */
void edi_scm_status(void);

/**
 * Move from src to dest.
 *
 * @param src The source file,
 * @param dest The destination.
 *
 * @return The status code of command executed.
 * @ingroup Scm
 */
int edi_scm_move(const char *src, const char *dest);

/**
 * Set user credentials for the SCM system.
 *
 * @param user The name of the user.
 * @param email The email of the user.
 *
 * @return The status code of command executed.
 *
 * @ingroup Scm
 */
int edi_scm_credits(const char *user, const char *email);

/**
 * Push to SCM remote repository.
 *
 * @ingroup Scm
 */
void edi_scm_push(void);

/**
 * Pull from SCM remote repository.
 *
 * @ingroup Scm
 */
void edi_scm_pull(void);

/**
 * Stash local changes.
 *
 * @ingroup Scm
 */
void edi_scm_stash(void);

/**
 * Set remote url for SCM.
 *
 * @param message The remote_url to add.
 *
 * @return The status code of command executed.
 *
 * @ingroup Scm
 */
int edi_scm_remote_add(const char *remote_url);

/**
 * Test whether SCM is enabled for this project.
 *
 * @return Whether SCM is enabled or not (true/false);
 *
 * @ingroup Scm
 */
Eina_Bool edi_scm_enabled(void);

/**
 * Test whether SCM has a remote enabled for this project.
 *
 * @return Whether SCM is remote enabled or not (true/false);
 *
 * @ingroup Scm
 */
Eina_Bool edi_scm_remote_enabled(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* EDI_SCM_H_ */