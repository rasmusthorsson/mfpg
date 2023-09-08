// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/XsString.h"
#include "mx/core/elements/RightsAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( RightsAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Rights )

        inline RightsPtr makeRights() { return std::make_shared<Rights>(); }
		inline RightsPtr makeRights( const XsString& value ) { return std::make_shared<Rights>( value ); }
		inline RightsPtr makeRights( XsString&& value ) { return std::make_shared<Rights>( std::move( value ) ); }

        class Rights : public ElementInterface
        {
        public:
            Rights();
            Rights( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            RightsAttributesPtr getAttributes() const;
            void setAttributes( const RightsAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            XsString myValue;
            RightsAttributesPtr myAttributes;
        };
    }
}
