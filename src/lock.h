/* *INDENT-OFF* */
#if (CPUS > 1)
#  if !defined(UNIX)
/*
 *******************************************************************************
 *                                                                             *
 *  this is a Microsoft windows-based operating system.                        *
 *                                                                             *
 *******************************************************************************
 */
#    include <windows.h>
#    define pthread_attr_t  HANDLE
#    define pthread_t       HANDLE
#    define thread_t        HANDLE
extern pthread_t NumaStartThread(void *func, void *args);

#    include <windows.h>
typedef volatile LONG lock_t[1];

#    define LockInit(v)      ((v)[0] = 0)
#    define LockFree(v)      ((v)[0] = 0)
#    define Unlock(v)        ((v)[0] = 0)
__forceinline void Lock(volatile LONG * hPtr) {
  int iValue;

  for (;;) {
    iValue = _InterlockedExchange((LPLONG) hPtr, 1);
    if (0 == iValue)
      return;
    while (*hPtr);
  }
}
void Pause() {
}
#  else
/*
 *******************************************************************************
 *                                                                             *
 *  this is a Unix-based operating system.  define the spinlock code as needed *
 *  for SMP synchronization.                                                   *
 *                                                                             *
 *******************************************************************************
 */
#    include <pthread.h>
#    define lock_t                pthread_mutex_t
#    define LockInit(p)           (pthread_mutex_init(&p, NULL))
#    define Unlock(p)             (pthread_mutex_unlock(&p))
#    define Lock(p)               (pthread_mutex_lock(&p))
#  endif
#else
#  define LockInit(p)
#  define LockFree(p)
#  define Lock(p)
#  define Unlock(p)
#  define lock_t                volatile int
#endif /*  SMP code */
/* *INDENT-ON* */
