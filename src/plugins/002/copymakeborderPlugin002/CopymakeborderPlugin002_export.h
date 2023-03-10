
#ifndef COPYMAKEBORDERPLUGIN002_EXPORT_H
#define COPYMAKEBORDERPLUGIN002_EXPORT_H

#ifdef COPYMAKEBORDERPLUGIN002_STATIC_DEFINE
#  define COPYMAKEBORDERPLUGIN002_EXPORT
#  define COPYMAKEBORDERPLUGIN002_NO_EXPORT
#else
#  ifndef COPYMAKEBORDERPLUGIN002_EXPORT
#    ifdef copymakeborderPlugin002_EXPORTS
        /* We are building this library */
#      define COPYMAKEBORDERPLUGIN002_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define COPYMAKEBORDERPLUGIN002_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef COPYMAKEBORDERPLUGIN002_NO_EXPORT
#    define COPYMAKEBORDERPLUGIN002_NO_EXPORT 
#  endif
#endif

#ifndef COPYMAKEBORDERPLUGIN002_DEPRECATED
#  define COPYMAKEBORDERPLUGIN002_DEPRECATED __declspec(deprecated)
#endif

#ifndef COPYMAKEBORDERPLUGIN002_DEPRECATED_EXPORT
#  define COPYMAKEBORDERPLUGIN002_DEPRECATED_EXPORT COPYMAKEBORDERPLUGIN002_EXPORT COPYMAKEBORDERPLUGIN002_DEPRECATED
#endif

#ifndef COPYMAKEBORDERPLUGIN002_DEPRECATED_NO_EXPORT
#  define COPYMAKEBORDERPLUGIN002_DEPRECATED_NO_EXPORT COPYMAKEBORDERPLUGIN002_NO_EXPORT COPYMAKEBORDERPLUGIN002_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COPYMAKEBORDERPLUGIN002_NO_DEPRECATED
#    define COPYMAKEBORDERPLUGIN002_NO_DEPRECATED
#  endif
#endif

#endif /* COPYMAKEBORDERPLUGIN002_EXPORT_H */
