// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <cstdint>
#include <optional>

#include <ATen/Device.h>
#include <ATen/ScalarType.h>
#include <ATen/Tensor.h>

#include "fairseq2/native/api.h"
#include "fairseq2/native/span.h"
#include "fairseq2/native/data/data.h"
#include "fairseq2/native/data/data_processor.h"

namespace fairseq2 {

class sp_encoder_options {
public:
    sp_encoder_options &
    enable_sampling(bool value) noexcept
    {
        enable_sampling_ = value;

        return *this;
    }

    bool
    enable_sampling() const noexcept
    {
        return enable_sampling_;
    }

    sp_encoder_options &
    nbest_size(std::int32_t value) noexcept
    {
        nbest_size_ = value;

        return *this;
    }

    std::int32_t
    nbest_size() const noexcept
    {
        return nbest_size_;
    }

    sp_encoder_options &
    alpha(float value) noexcept
    {
        alpha_ = value;

        return *this;
    }

    float
    alpha() const noexcept
    {
        return alpha_;
    }

    sp_encoder_options &
    batch_size(std::optional<std::int64_t> value) noexcept
    {
        batch_size_ = value;

        return *this;
    }

    std::optional<std::int64_t>
    batch_size() const noexcept
    {
        return batch_size_;
    }

    sp_encoder_options &
    pad_to_length(std::optional<std::int64_t> value) noexcept
    {
        pad_to_length_ = value;

        return *this;
    }

    std::optional<std::int64_t>
    pad_to_length() const noexcept
    {
        return pad_to_length_;
    }

    sp_encoder_options &
    pad_to_multiple(std::int64_t value) noexcept
    {
        pad_to_multiple_ = value;

        return *this;
    }

    std::int64_t
    pad_to_multiple() const noexcept
    {
        return pad_to_multiple_;
    }

    sp_encoder_options &
    left_pad(bool value) noexcept
    {
        left_pad_ = value;

        return *this;
    }

    bool
    left_pad() const noexcept
    {
        return left_pad_;
    }

    sp_encoder_options &
    dtype(at::ScalarType value) noexcept
    {
        dtype_ = value;

        return *this;
    }

    at::ScalarType
    dtype() const noexcept
    {
        return dtype_;
    }

    sp_encoder_options &
    device(std::optional<at::Device> value) noexcept
    {
        device_ = value;

        return *this;
    }

    std::optional<at::Device>
    device() const noexcept
    {
        return device_;
    }

    sp_encoder_options &
    pin_memory(bool value) noexcept
    {
        pin_memory_ = value;

        return *this;
    }

    bool
    pin_memory() const noexcept
    {
        return pin_memory_;
    }

    sp_encoder_options &
    disable_parallelism(bool value) noexcept
    {
        disable_parallelism_ = value;

        return *this;
    }

    bool
    disable_parallelism() const noexcept
    {
        return disable_parallelism_;
    }

private:
    bool enable_sampling_{};
    std::int32_t nbest_size_ = -1;
    float alpha_ = 0.1F;
    std::optional<std::int64_t> batch_size_{};
    std::optional<std::int32_t> pad_idx_{};
    std::optional<std::int64_t> pad_to_length_{};
    std::int64_t pad_to_multiple_ = 1;
    bool left_pad_ = false;
    at::ScalarType dtype_ = at::kInt;
    std::optional<at::Device> device_{};
    bool pin_memory_ = false;
    bool disable_parallelism_ = false;
};

class sp_model;

class FAIRSEQ2_API sp_encoder final : public data_processor {
public:
    explicit
    sp_encoder(const sp_model *m, sp_encoder_options opts = {});

    data
    operator()(data &&d) const override;

private:
    at::Tensor
    encode(span<data> texts) const;

private:
    const sp_model *model_;
    sp_encoder_options opts_;
};

}  // namespace fairseq2