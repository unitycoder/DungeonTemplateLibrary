﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_TYPE_VECTOR_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_TYPE_VECTOR_HPP


#ifndef DTL_TYPE_VECTOR


#if defined(UE_BUILD_FINAL_RELEASE) //UE4

#include <DTL/Type/SizeT.hpp>
#define DTL_TYPE_VECTOR ::TArray
#ifndef DTL_TYPE_VSIZE
#define DTL_TYPE_VSIZE Num
#endif
#ifndef DTL_TYPE_VEMPLACE
#define DTL_TYPE_VEMPLACE Emplace
#endif
#ifndef DTL_TYPE_VPUSH
#define DTL_TYPE_VPUSH Add
#endif

namespace dtl {
	namespace type {
		template<typename Int_>
		DTL_TYPE_VECTOR<Int_> makeVector(const ::dtl::type::size size_, const Int_& int_) noexcept {
			DTL_TYPE_VECTOR<Int_> mv{};
			mv.Init(int_, size_);
			return mv;
		}
	}
}

#else

#include <vector>
#include <DTL/Type/SizeT.hpp>
#define DTL_TYPE_VECTOR ::std::vector
#ifndef DTL_TYPE_VSIZE
#define DTL_TYPE_VSIZE size
#endif
#ifndef DTL_TYPE_VEMPLACE
#define DTL_TYPE_VEMPLACE emplace_back
#endif
#ifndef DTL_TYPE_VPUSH
#define DTL_TYPE_VPUSH push_back
#endif

namespace dtl {
	namespace type {
		template<typename Int_>
		DTL_TYPE_VECTOR<Int_> makeVector(const ::dtl::type::size size_, const Int_& int_) noexcept {
			return DTL_TYPE_VECTOR<Int_>(size_, int_);
		}
	}
}

#endif


#endif


#endif //Included Dungeon Template Library