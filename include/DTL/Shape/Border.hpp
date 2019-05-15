﻿/*
#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Utility/DrawJagged.hpp>
#include <DTL/Utility/RectBaseWithValue.hpp>

namespace dtl {
	inline namespace shape {

		//マップの外枠を指定した数値で埋める
		template<typename Matrix_Int_>
		class Border : public RectBaseWithValue<Border<Matrix_Int_>, Matrix_Int_>,
		               public DrawJagged<Border<Matrix_Int_>, Matrix_Int_> {
		private:


			///// エイリアス /////

			using Index_Size = ::dtl::type::size;
			using ShapeBase_t = RectBaseWithValue<Border<Matrix_Int_>, Matrix_Int_>;
			using DrawBase_t = DrawJagged<Border<Matrix_Int_>, Matrix_Int_>;

			friend DrawBase_t;


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_, typename = typename std::enable_if<Matrix_::is_jagged::value>::type>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawNormal(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				const Index_Size end_y_ = this->calcEndY(matrix_.getY());
				if (end_y_ <= this->start_y) return true;
				const Index_Size last_x1 = this->calcEndX(matrix_.getX(this->start_y));
				for (Index_Size col{ this->start_x }; col < last_x1; ++col)
					matrix_.set(col, this->start_y, this->draw_value, args_...);
				const Index_Size last_x2 = this->calcEndX(matrix_.getX(end_y_ - 1));
				for (Index_Size col{ this->start_x }; col < last_x2; ++col)
					matrix_.set(col, end_y_ - 1, this->draw_value, args_...);
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					const Index_Size last_x3 = this->calcEndX(matrix_.getX(row));
					if (last_x3 <= this->start_x) continue;
					matrix_.set(this->start_x, row, this->draw_value, args_...);
					matrix_.set(last_x3 - 1, row, this->draw_value, args_...);
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawNormal(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				const Index_Size end_x_ = this->calcEndX(matrix_.getX());
				const Index_Size end_y_ = this->calcEndY(matrix_.getY());
				if (end_x_ <= this->start_x || end_y_ <= this->start_y) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					matrix_.set(col, this->start_y, this->draw_value, args_...);
					matrix_.set(col, end_y_ - 1, this->draw_value, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					matrix_.set(this->start_x, row, this->draw_value, args_...);
					matrix_.set(end_x_ - 1, row, this->draw_value, args_...);
				}
				return true;
			}

		public:


			///// コンストラクタ /////

			using ShapeBase_t::ShapeBase_t;
		};
	}
}

#endif //Included Dungeon Template Library
*/

/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_BORDER_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_BORDER_HPP

/*#######################################################################################
	日本語リファレンス (Reference-JP)
	https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/::dtl::shape::Border-(%E5%BD%A2%E7%8A%B6%E3%82%AF%E3%83%A9%E3%82%B9)/
#######################################################################################*/

/* Character Code : UTF-8 (BOM) */
/* Bug Check : already checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>

namespace dtl {
	inline namespace shape {

		//マップの外枠を指定した数値で埋める
		template<typename Matrix_Int_>
		class Border {
		private:


			///// エイリアス /////

			using Index_Size = ::dtl::type::size;



			///// メンバ変数 /////

			Index_Size start_x{};
			Index_Size start_y{};
			Index_Size width{};
			Index_Size height{};
			Matrix_Int_ draw_value{};


			///// 代入処理 /////

			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionSTL(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_) const noexcept {
				matrix_[end_y_][end_x_] = this->draw_value;
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionArray(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_) const noexcept {
				matrix_[end_y_ * max_x_ + end_x_] = this->draw_value;
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionLayer(Matrix_&& matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_) const noexcept {
				matrix_[end_y_][end_x_][layer_] = this->draw_value;
			}

			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionSTL(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, Function_&& function_) const noexcept {
				if (function_(matrix_[end_y_][end_x_])) matrix_[end_y_][end_x_] = this->draw_value;
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionArray(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_, Function_&& function_) const noexcept {
				if (function_(matrix_[end_y_ * max_x_ + end_x_])) matrix_[end_y_ * max_x_ + end_x_] = this->draw_value;
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionLayer(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Function_ && function_) const noexcept {
				if (function_(matrix_[end_y_][end_x_][layer_])) matrix_[end_y_][end_x_][layer_] = this->draw_value;
			}


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawSTL(Matrix_ && matrix_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < matrix_[this->start_y].size(); ++col)
					this->substitutionSTL(matrix_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < matrix_[end_y_ - 1].size(); ++col)
					this->substitutionSTL(matrix_, col, end_y_ - 1, args_...);
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->substitutionSTL(matrix_, this->start_x, row, args_...);
					this->substitutionSTL(matrix_, matrix_[row].size() - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawWidthSTL(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[this->start_y].size(); ++col)
					this->substitutionSTL(matrix_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[end_y_ - 1].size(); ++col)
					this->substitutionSTL(matrix_, col, end_y_ - 1, args_...);
				if (end_x_ == 0) return true;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->substitutionSTL(matrix_, this->start_x, row, args_...);
					if (matrix_[row].size() <= end_x_) this->substitutionSTL(matrix_, matrix_[row].size() - 1, row, args_...);
					else this->substitutionSTL(matrix_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//LayerSTL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < matrix_[this->start_y].size(); ++col)
					this->substitutionLayer(matrix_, layer_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < matrix_[end_y_ - 1].size(); ++col)
					this->substitutionLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->substitutionLayer(matrix_, layer_, this->start_x, row, args_...);
					this->substitutionLayer(matrix_, layer_, matrix_[row].size() - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerWidthSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[this->start_y].size(); ++col)
					this->substitutionLayer(matrix_, layer_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[end_y_ - 1].size(); ++col)
					this->substitutionLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				if (end_x_ == 0) return true;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->substitutionLayer(matrix_, layer_, this->start_x, row, args_...);
					if (matrix_[row].size() <= end_x_) this->substitutionLayer(matrix_, layer_, matrix_[row].size() - 1, row, args_...);
					else this->substitutionLayer(matrix_, layer_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawNormal(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_x_ == 0 || end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->substitutionSTL(matrix_, col, this->start_y, args_...);
					this->substitutionSTL(matrix_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->substitutionSTL(matrix_, this->start_x, row, args_...);
					this->substitutionSTL(matrix_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//LayerNormal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerNormal(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_x_ == 0 || end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->substitutionLayer(matrix_, layer_, col, this->start_y, args_...);
					this->substitutionLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->substitutionLayer(matrix_, layer_, this->start_x, row, args_...);
					this->substitutionLayer(matrix_, layer_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//Array
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawArray(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_, Args_ && ... args_) const noexcept {
				if (end_x_ == 0 || end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->substitutionArray(matrix_, col, this->start_y, max_x_, args_...);
					this->substitutionArray(matrix_, col, end_y_ - 1, max_x_, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->substitutionArray(matrix_, this->start_x, row, max_x_, args_...);
					this->substitutionArray(matrix_, end_x_ - 1, row, max_x_, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

		public:


			///// 情報取得 /////

			DTL_VERSIONING_CPP17_NODISCARD
				constexpr Index_Size getPointX() const noexcept {
				return this->start_x;
			}
			DTL_VERSIONING_CPP17_NODISCARD
				constexpr Index_Size getPointY() const noexcept {
				return this->start_y;
			}
			DTL_VERSIONING_CPP17_NODISCARD
				constexpr Index_Size getWidth() const noexcept {
				return this->width;
			}
			DTL_VERSIONING_CPP17_NODISCARD
				constexpr Index_Size getHeight() const noexcept {
				return this->height;
			}
			DTL_VERSIONING_CPP17_NODISCARD
				constexpr Matrix_Int_ getValue() const noexcept {
				return this->draw_value;
			}


			///// 生成呼び出し /////

			//STL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height) : this->drawWidthSTL(matrix_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_) : this->drawWidthSTL(matrix_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_);
			}

			//LayerSTL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_);
			}

			//Normal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, function_);
			}

			//LayerNormal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, function_);
			}

			//Array
			template<typename Matrix_>
			constexpr bool drawArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, max_x_);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperatorArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, max_x_, function_);
			}


			///// 生成呼び出しファンクタ /////

			template<typename Matrix_, typename ...Args_>
			constexpr bool operator()(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				return this->draw(DTL_TYPE_FORWARD<Matrix_>(matrix_), DTL_TYPE_FORWARD<Args_>(args_)...);
			}


			///// ダンジョン行列生成 /////

			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& create(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->draw(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawArray(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createOperator(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperator(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createOperatorArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperatorArray(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}


			///// 消去 /////

			//始点座標Xを初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearPointX() noexcept {
				this->start_x = 0;
				return *this;
			}
			//始点座標Yを初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearPointY() noexcept {
				this->start_y = 0;
				return *this;
			}
			//範囲の大きさ(X軸方向)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearWidth() noexcept {
				this->width = 0;
				return *this;
			}
			//範囲の大きさ(Y軸方向)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearHeight() noexcept {
				this->height = 0;
				return *this;
			}
			//塗り値を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearValue() noexcept {
				const Matrix_Int_ new_draw_value{};
				this->draw_value = new_draw_value;
				return *this;
			}
			//始点座標(X,Y)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearPoint() noexcept {
				this->clearPointX();
				this->clearPointY();
				return *this;
			}
			//描画範囲を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clearRange() noexcept {
				this->clearPointX();
				this->clearPointY();
				this->clearWidth();
				this->clearHeight();
				return *this;
			}
			//全ての値を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& clear() noexcept {
				this->clearRange();
				this->clearValue();
				return *this;
			}


			///// 代入 /////

			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setPointX(const Index_Size end_x_) noexcept {
				this->start_x = end_x_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setPointY(const Index_Size end_y_) noexcept {
				this->start_y = end_y_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setWidth(const Index_Size width_) noexcept {
				this->width = width_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setHeight(const Index_Size height_) noexcept {
				this->height = height_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setValue(const Matrix_Int_ & draw_value_) noexcept {
				this->draw_value = draw_value_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setPoint(const Index_Size point_) noexcept {
				this->start_x = point_;
				this->start_y = point_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setPoint(const Index_Size end_x_, const Index_Size end_y_) noexcept {
				this->start_x = end_x_;
				this->start_y = end_y_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setRange(const Index_Size end_x_, const Index_Size end_y_, const Index_Size length_) noexcept {
				this->start_x = end_x_;
				this->start_y = end_y_;
				this->width = length_;
				this->height = length_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setRange(const Index_Size end_x_, const Index_Size end_y_, const Index_Size width_, const Index_Size height_) noexcept {
				this->start_x = end_x_;
				this->start_y = end_y_;
				this->width = width_;
				this->height = height_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				Border& setRange(const ::dtl::base::MatrixRange & matrix_range_) noexcept {
				this->start_x = matrix_range_.x;
				this->start_y = matrix_range_.y;
				this->width = matrix_range_.w;
				this->height = matrix_range_.h;
				return *this;
			}


			///// コンストラクタ /////

			constexpr Border() noexcept = default;
			constexpr explicit Border(const Matrix_Int_ & draw_value_) noexcept
				:draw_value(draw_value_) {}
			constexpr explicit Border(const ::dtl::base::MatrixRange & matrix_range_) noexcept
				:start_x(matrix_range_.x), start_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h) {}
			constexpr explicit Border(const ::dtl::base::MatrixRange & matrix_range_, const Matrix_Int_ & draw_value_) noexcept
				:start_x(matrix_range_.x), start_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				draw_value(draw_value_) {}
			constexpr explicit Border(const Index_Size end_x_, const Index_Size end_y_, const Index_Size width_, const Index_Size height_) noexcept
				:start_x(end_x_), start_y(end_y_),
				width(width_), height(height_) {}
			constexpr explicit Border(const Index_Size end_x_, const Index_Size end_y_, const Index_Size width_, const Index_Size height_, const Matrix_Int_ & draw_value_) noexcept
				:start_x(end_x_), start_y(end_y_),
				width(width_), height(height_),
				draw_value(draw_value_) {}
		};
	}
}

#endif //Included Dungeon Template Library