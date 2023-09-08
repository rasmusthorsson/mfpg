// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Date.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( EncodingDate )

        inline EncodingDatePtr makeEncodingDate() { return std::make_shared<EncodingDate>(); }
		inline EncodingDatePtr makeEncodingDate( const Date& value ) { return std::make_shared<EncodingDate>( value ); }
		inline EncodingDatePtr makeEncodingDate( Date&& value ) { return std::make_shared<EncodingDate>( std::move( value ) ); }

        class EncodingDate : public ElementInterface
        {
        public:
            EncodingDate();
            EncodingDate( const Date& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            Date getValue() const;
            void setValue( const Date& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            Date myValue;
        };
    }
}
