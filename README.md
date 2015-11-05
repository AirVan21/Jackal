# Jackal

### Information

Jackal is a project for distributed video encoding.

Main entities are :
* client (needs to encode video file)
* server (finds recources for distributed encoding)
* worker (is a recource unit, encodes video file)

Extra information could be find [Jackal on mit.spbau.ru] (http://mit.spbau.ru/sewiki/index.php/%D0%A0%D0%B0%D1%81%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%BD%D0%BE%D0%B5_%D0%BA%D0%BE%D0%B4%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%B2%D0%B8%D0%B4%D0%B5%D0%BE)

### Build && Run

To build and run the project you will need:

* Qt 5
* g++ v4.9.3 
* mkvmerge v8.5.2 ('Crosses')
* ffmpeg (version N-76045-g97be5d4 or later) with componetns:
   
   libavutil      55.  4.100 / 55.  4.100  libavcodec     57.  6.100 / 57.  6.100
   libavformat    57.  4.100 / 57.  4.100  libavdevice    57.  0.100 / 57.  0.100
   libavfilter     6. 11.100 /  6. 11.100  libavresample   3.  0.  0 /  3.  0.  0
   libswscale      4.  0.100 /  4.  0.100  libswresample   2.  0.100 /  2.  0.100
   libpostproc    54.  0.100 / 54.  0.100
