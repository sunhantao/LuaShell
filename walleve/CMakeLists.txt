#------------------------------------------------------------------------------
# CMake file for Multiverse
#
# Copyright (c) 2016 The Multiverse developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#------------------------------------------------------------------------------

set(sources
	walleve/version.h
	walleve/type.h
        walleve/util.cpp		walleve/util.h
       	walleve/rwlock.h
	walleve/compacttv.h
	walleve/entry/entry.cpp		walleve/entry/entry.h
	walleve/event/event.cpp		walleve/event/event.h
	walleve/event/eventproc.cpp	walleve/event/eventproc.h
	walleve/stream/circular.cpp	walleve/stream/circular.h
	walleve/stream/stream.cpp	walleve/stream/stream.h
	walleve/base/base.cpp		walleve/base/base.h
	walleve/docker/config.cpp	walleve/docker/config.h
	walleve/docker/docker.cpp	walleve/docker/docker.h
	walleve/netio/nethost.cpp	walleve/netio/nethost.h
	walleve/netio/ioclient.cpp	walleve/netio/ioclient.h
	walleve/netio/iocontainer.cpp	walleve/netio/iocontainer.h
	walleve/netio/ioproc.cpp	walleve/netio/ioproc.h
	walleve/console/console.cpp	walleve/console/console.h
	walleve/peernet/nodemngr.cpp	walleve/peernet/nodemngr.h
	walleve/peernet/epmngr.cpp	walleve/peernet/epmngr.h
	walleve/peernet/peer.cpp	walleve/peernet/peer.h
	walleve/peernet/peernet.cpp	walleve/peernet/peernet.h
	walleve/peernet/datasched.h
	walleve/http/httpcookie.cpp	walleve/http/httpcookie.h
	walleve/http/httpsse.cpp	walleve/http/httpsse.h
	walleve/http/httputil.cpp	walleve/http/httputil.h
	walleve/http/httpserver.cpp	walleve/http/httpserver.h
	walleve/http/httpget.cpp	walleve/http/httpget.h
	walleve/db/kvdb.h
	walleve/stream/datastream.h
	walleve/docker/log.h  
	walleve/docker/nettime.h  
	walleve/docker/thread.h  
	walleve/docker/timer.h
	walleve/netio/netio.h
	walleve/http/httptype.h
	walleve/http/httpevent.h
	walleve/peernet/peerevent.h
	walleve/peernet/peerinfo.h
)

add_library(walleve ${sources})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(./)

target_link_libraries(walleve
	Boost::system
	Boost::filesystem
	Boost::program_options
	Boost::thread
	Boost::date_time
	Boost::regex
	OpenSSL::SSL
	OpenSSL::Crypto
	${Readline_LIBRARY}
)
