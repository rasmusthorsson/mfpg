// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/api/ApiCommon.h"
#include "mx/api/PageLayoutData.h"

#include <optional>
#include <string>
#include <vector>

namespace mx
{
    namespace api
    {
        /// PageData allows the specification of a new page, or the prevention of a new page, along with the ability
        /// to change the page layout settings. In the score these are stored in a map where the map key is the measure
        /// index of where the PageData takes effect in the score.
        class PageData
        {
        public:
            inline explicit PageData(
                Bool inNewPage = Bool::unspecified,
                PageLayoutData inPageLayoutData = PageLayoutData{},
                std::optional<std::string> inPageNumber = std::nullopt
            )
                : newPage{ inNewPage }
                , pageLayoutData{ inPageLayoutData }
                , pageNumber{ std::move( inPageNumber ) }
            {

            }

            /// `yes` will cause a page break at the specified measure index or system index. `no` indicates that a
            /// page break should be avoided. 'unspecified' means that no page-break attribute will be shown.
            Bool newPage;

            /// Optionally change the page layout settings starting with this page (and continuing thereafter). The
            /// default constructed PageLayoutData will not affect page layout. Page layout information will only be
            /// written if you set one or more of its optional values.
            PageLayoutData pageLayoutData;

            /// The displayed page number. std::nullopt indicates the absence of a page-number attribute.
            std::optional<std::string> pageNumber;

            /// Indicates whether any values have been assigned.
            inline bool isUsed() const
            {
                return isSpecified( newPage ) || pageLayoutData.isUsed() || pageNumber;
            }
        };

        MXAPI_EQUALS_BEGIN( PageData )
            MXAPI_EQUALS_MEMBER( newPage )
            MXAPI_EQUALS_MEMBER( pageLayoutData )
            MXAPI_EQUALS_MEMBER( pageNumber )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( PageData );
    }
}
