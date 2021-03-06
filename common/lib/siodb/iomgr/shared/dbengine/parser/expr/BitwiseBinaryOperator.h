// Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
// Use of this source code is governed by a license that can be found
// in the LICENSE file.

#pragma once

// Project headers
#include "BinaryOperator.h"

namespace siodb::iomgr::dbengine::requests {

/** A base class for bitwise binary operators &, |, ^, >>, << */
class BitwiseBinaryOperator : public BinaryOperator {
protected:
    /**
     * Initializes object of class BitwiseBinaryOperator.
     * @param type Expression type.
     * @param left Left operand.
     * @param right Right operand.
     * @throw std::invalid_argument if left is nullptr
     */
    BitwiseBinaryOperator(ExpressionType type, ExpressionPtr&& left, ExpressionPtr&& right) noexcept
        : BinaryOperator(type, std::move(left), std::move(right))
    {
    }

public:
    /**
     * Returns value type of expression.
     * @param context Evaluation context.
     * @return Evaluated expression value type.
     */
    VariantType getResultValueType(const ExpressionEvaluationContext& context) const override;

    /**
     * Returns type of generated column from this expression.
     * @param context Evaluation context.
     * @return Column data type.
     */
    ColumnDataType getColumnDataType(const ExpressionEvaluationContext& context) const override;

    /**
     * Checks if operands are integer and valid.
     * @param context Evaluation context.
     * @std::runtime_error if operands aren't integer or not valid
     */
    void validate(const ExpressionEvaluationContext& context) const override;
};

}  // namespace siodb::iomgr::dbengine::requests
