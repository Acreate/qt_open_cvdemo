
#ifndef FILTERPLUGIN002_EXPORT_H
#define FILTERPLUGIN002_EXPORT_H

#ifdef FILTERPLUGIN002_STATIC_DEFINE
#  define FILTERPLUGIN002_EXPORT
#  define FILTERPLUGIN002_NO_EXPORT
#else
#  ifndef FILTERPLUGIN002_EXPORT
#    ifdef filterPlugin002_EXPORTS
        /* We are building this library */
#      define FILTERPLUGIN002_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define FILTERPLUGIN002_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef FILTERPLUGIN002_NO_EXPORT
#    define FILTERPLUGIN002_NO_EXPORT 
#  endif
#endif

#ifndef FILTERPLUGIN002_DEPRECATED
#  define FILTERPLUGIN002_DEPRECATED __declspec(deprecated)
#endif

#ifndef FILTERPLUGIN002_DEPRECATED_EXPORT
#  define FILTERPLUGIN002_DEPRECATED_EXPORT FILTERPLUGIN002_EXPORT FILTERPLUGIN002_DEPRECATED
#endif

#ifndef FILTERPLUGIN002_DEPRECATED_NO_EXPORT
#  define FILTERPLUGIN002_DEPRECATED_NO_EXPORT FILTERPLUGIN002_NO_EXPORT FILTERPLUGIN002_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FILTERPLUGIN002_NO_DEPRECATED
#    define FILTERPLUGIN002_NO_DEPRECATED
#  endif
#endif

#endif /* FILTERPLUGIN002_EXPORT_H */
