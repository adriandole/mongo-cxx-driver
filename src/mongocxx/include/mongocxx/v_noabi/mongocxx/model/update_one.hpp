// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <mongocxx/model/update_one-fwd.hpp>

#include <bsoncxx/array/view_or_value.hpp>
#include <bsoncxx/document/view_or_value.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <mongocxx/hint.hpp>
#include <mongocxx/pipeline.hpp>
#include <mongocxx/stdx.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
inline namespace v_noabi {
namespace model {

///
/// Class representing a MongoDB update operation that modifies a single document.
///
class update_one {
    //
    // Utility class supporting the convenience of {} meaning an empty bsoncxx::document.
    //
    // Users may not use this class directly.
    //
    // In places where driver methods take this class as a parameter, passing {} will
    // translate to a default-constructed bsoncxx::document::view_or_value,
    // regardless of other overloads taking other default-constructible types
    // for that parameter. This class avoids compiler ambiguity with such overloads.
    //
    // See update_one() for an example of such overloads.
    //
    class _empty_doc_tag {
        _empty_doc_tag() = default;
    };

   public:
    ///
    /// @{
    ///
    /// Constructs an update operation that will modify a single document matching the filter.
    ///
    /// @param filter
    ///   Document representing the criteria for applying the update.
    /// @param update
    ///   Document representing the modifications to be applied to the matching document.
    ///
    update_one(bsoncxx::document::view_or_value filter, bsoncxx::document::view_or_value update);

    ///
    /// Constructs an update operation that will modify a single document matching the filter.
    ///
    /// @param filter
    ///   Document representing the criteria for applying the update.
    /// @param update
    ///   Pipeline representing the modifications to be applied to the matching document.
    ///
    update_one(bsoncxx::document::view_or_value filter, const pipeline& update);

    ///
    /// Constructs an update operation that will modify a single document matching the filter.
    ///
    /// @param filter
    ///   Document representing the criteria for applying the update.
    /// @param update
    ///   Supports the empty update {}.
    ///
    update_one(bsoncxx::document::view_or_value filter,
               std::initializer_list<_empty_doc_tag> update);

    ///
    /// @}
    ///

    ///
    /// Gets the filter
    ///
    /// @return The filter to be used for the update operation.
    ///
    const bsoncxx::document::view_or_value& filter() const;

    ///
    /// Gets the update document.
    ///
    /// @return The modifications to be applied as part of the update.
    ///
    const bsoncxx::document::view_or_value& update() const;

    ///
    /// Sets the collation for this update operation.
    ///
    /// @param collation
    ///   The new collation.
    ///
    /// @see
    ///   https://www.mongodb.com/docs/manual/reference/collation/
    ///
    update_one& collation(bsoncxx::document::view_or_value collation);

    ///
    /// Gets the collation option for this update operation.
    ///
    /// @return
    ///   The optional value of the collation option.
    ///
    /// @see
    ///   https://www.mongodb.com/docs/manual/reference/collation/
    ///
    const stdx::optional<bsoncxx::document::view_or_value>& collation() const;

    ///
    /// Sets the index to use for this operation.
    ///
    /// @note if the server already has a cached shape for this query, it may
    /// ignore a hint.
    ///
    /// @param index_hint
    ///   Object representing the index to use.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    update_one& hint(mongocxx::hint index_hint);

    ///
    /// Gets the current hint.
    ///
    /// @return The current hint, if one is set.
    ///
    const stdx::optional<mongocxx::hint>& hint() const;

    ///
    /// Sets the upsert option.
    ///
    /// When upsert is @c false, if no document matches the filter, update does nothing.
    /// However, by specifying upsert as @c true, this operation either updates a matching document
    /// or inserts a new document using the update specification if no matching document exists.
    /// By default upsert is @c false.
    ///
    /// @param upsert
    ///   If set to @c true, creates a new document when no document matches the query criteria.
    ///   The server side default is @c false, which does not insert a new document if a match
    ///   is not found.
    ///
    update_one& upsert(bool upsert);

    ///
    /// Gets the current value of the upsert option.
    ///
    /// @return The optional value of the upsert option.
    ///
    const stdx::optional<bool>& upsert() const;

    ///
    /// Set array filters for this update operation.
    ///
    /// @param array_filters
    ///   Array representing filters determining which array elements to modify.
    ///
    /// @see https://www.mongodb.com/docs/manual/reference/command/update/
    ///
    update_one& array_filters(bsoncxx::array::view_or_value array_filters);

    ///
    /// Get array filters for this operation.
    ///
    /// @return
    ///   The current array filters.
    ///
    /// @see https://www.mongodb.com/docs/manual/reference/command/update/
    ///
    const stdx::optional<bsoncxx::array::view_or_value>& array_filters() const;

   private:
    bsoncxx::document::view_or_value _filter;
    bsoncxx::document::view_or_value _update;

    stdx::optional<bsoncxx::document::view_or_value> _collation;
    stdx::optional<bsoncxx::array::view_or_value> _array_filters;
    stdx::optional<bool> _upsert;
    stdx::optional<mongocxx::hint> _hint;
};

}  // namespace model
}  // namespace v_noabi
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>
