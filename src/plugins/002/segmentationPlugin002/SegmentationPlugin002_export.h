
#ifndef SEGMENTATIONPLUGIN002_EXPORT_H
#define SEGMENTATIONPLUGIN002_EXPORT_H

#ifdef SEGMENTATIONPLUGIN002_STATIC_DEFINE
#  define SEGMENTATIONPLUGIN002_EXPORT
#  define SEGMENTATIONPLUGIN002_NO_EXPORT
#else
#  ifndef SEGMENTATIONPLUGIN002_EXPORT
#    ifdef segmentationPlugin002_EXPORTS
        /* We are building this library */
#      define SEGMENTATIONPLUGIN002_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define SEGMENTATIONPLUGIN002_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef SEGMENTATIONPLUGIN002_NO_EXPORT
#    define SEGMENTATIONPLUGIN002_NO_EXPORT 
#  endif
#endif

#ifndef SEGMENTATIONPLUGIN002_DEPRECATED
#  define SEGMENTATIONPLUGIN002_DEPRECATED __declspec(deprecated)
#endif

#ifndef SEGMENTATIONPLUGIN002_DEPRECATED_EXPORT
#  define SEGMENTATIONPLUGIN002_DEPRECATED_EXPORT SEGMENTATIONPLUGIN002_EXPORT SEGMENTATIONPLUGIN002_DEPRECATED
#endif

#ifndef SEGMENTATIONPLUGIN002_DEPRECATED_NO_EXPORT
#  define SEGMENTATIONPLUGIN002_DEPRECATED_NO_EXPORT SEGMENTATIONPLUGIN002_NO_EXPORT SEGMENTATIONPLUGIN002_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SEGMENTATIONPLUGIN002_NO_DEPRECATED
#    define SEGMENTATIONPLUGIN002_NO_DEPRECATED
#  endif
#endif

#endif /* SEGMENTATIONPLUGIN002_EXPORT_H */