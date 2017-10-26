#pragma once

#include <algorithm>
#include <array>

// A matrix Library to be simple and fast
// By Pooyan

namespace AMatrix {
	template <typename DataType, int NumberOfRows, int NumberOfColumns>
	class Matrix {
		DataType _data[NumberOfRows*NumberOfColumns];
	public:
		Matrix() {}
		Matrix(DataType const& InitialValue) {
			for (int i = 0; i < size(); i++)
				_data[i] = InitialValue;
		}

		Matrix(Matrix const& Other) {
			for (int i = 0; i < size(); i++)
				_data[i] = Other._data[i];
		}

		Matrix(Matrix&& Other) = default;

		template<typename TOtherMatrixType>
		explicit Matrix(TOtherMatrixType const& Other) {
			for (int i = 0; i < size1(); i++)
				for (int j = 0; j < size2(); j++)
					at(i, j) = Other(i, j);
		}

		Matrix& operator=(Matrix const& Other) {
			for (int i = 0; i < size(); i++)
				_data[i] = Other._data[i];
			return *this;
		}

		DataType& operator()(int i, int j) {
			return at(i,j);
		}

		DataType const& operator()(int i, int j) const {
			return at(i, j);
		}

		DataType& at(int i, int j) {
			return _data[i*NumberOfColumns + j];
		}

		DataType const& at(int i, int j) const {
			return _data[i*NumberOfColumns + j];
		}

		constexpr int size1() const {
			return NumberOfRows;
		}

		constexpr int size2() const {
			return NumberOfColumns;
		}

		constexpr int size() const {
			return NumberOfRows*NumberOfColumns;
		}

		friend bool operator==(Matrix const& First, Matrix const& Second) {
			for (int i = 0; i < First.size(); i++)
				if (First._data[i] != Second._data[i])
					return false;
			return true;
		}

		friend Matrix operator+(Matrix const& First, Matrix const& Second) {
			Matrix result;
			const DataType* __restrict first_data = First._data;
			const DataType* __restrict second_data = Second._data;
			DataType* __restrict result_data = result._data;
			for (int i = 0; i < First.size(); ++i)
				*result_data++ = *first_data++ + *second_data++;

			return result;
		}

		friend Matrix operator-(Matrix const& First, Matrix const& Second) {
			Matrix result;
			for (int i = 0; i < First.size(); ++i)
				result._data[i] = First._data[i] - Second._data[i];

			return result;
		}

		template<int SecondNumberOfColumns>
		friend inline Matrix<DataType, NumberOfRows, SecondNumberOfColumns> operator*(Matrix const& First, Matrix<DataType, NumberOfColumns, SecondNumberOfColumns> const& Second) {
			Matrix<DataType, NumberOfRows, SecondNumberOfColumns> result(0.00);
			DataType* result_row = result.data();
			const DataType* first_end = First.data() + First.size();
			for (const DataType* first_row = First.data(); first_row < first_end; first_row += NumberOfColumns) {
				for (int k = 0; k < Second.size1(); ++k) {
					ElementwiseMult<NumberOfColumns>(first_row, Second.data() + k * SecondNumberOfColumns, result_row);
				}
				result_row += SecondNumberOfColumns;
			}

			return result;
		}


		Matrix& noalias() {
			return *this;
		}

		DataType* data(){
			return _data;
		}

		DataType const* data() const {
			return _data;
		}

	private:
		template<int TSize>
		inline static void ElementwiseMult(const DataType* __restrict A, const DataType* __restrict B, DataType* C) {
			for (int i = 0; i < TSize; ++i) {
				*(C++) += *(A++) * *(B++);
			}
		}
	};

	template <typename DataType, int NumberOfRows, int NumberOfColumns>
	bool operator!=(Matrix<DataType, NumberOfRows, NumberOfColumns> const& First, Matrix<DataType, NumberOfRows, NumberOfColumns> const& Second) {
		return !(First == Second);
	}

	/// output stream function
	template <typename DataType, int NumberOfRows, int NumberOfColumns>
	inline std::ostream& operator << (std::ostream& rOStream,
		Matrix<DataType, NumberOfRows, NumberOfColumns> const& TheMatrix)
	{
		rOStream << "{";
		for (int i = 0; i < NumberOfRows; i++) {
			for (int j = 0; j < NumberOfColumns; j++)
				rOStream << TheMatrix(i, j) << ",";
			rOStream << std::endl;

		}
		rOStream << "}";

		return rOStream;
	}
} // mamespace AMatrix
