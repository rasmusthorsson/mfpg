// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/XsString.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( CreditType )

        inline CreditTypePtr makeCreditType() { return std::make_shared<CreditType>(); }
		inline CreditTypePtr makeCreditType( const XsString& value ) { return std::make_shared<CreditType>( value ); }
		inline CreditTypePtr makeCreditType( XsString&& value ) { return std::make_shared<CreditType>( std::move( value ) ); }

        class CreditType : public ElementInterface
        {
        public:
            CreditType();
            CreditType( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            XsString getValue() const;
            void setValue( const XsString& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            XsString myValue;
        };
    }
}
