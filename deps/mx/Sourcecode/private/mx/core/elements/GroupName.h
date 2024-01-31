// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/XsString.h"
#include "mx/core/elements/GroupNameAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GroupNameAttributes )
        MX_FORWARD_DECLARE_ELEMENT( GroupName )

        inline GroupNamePtr makeGroupName() { return std::make_shared<GroupName>(); }
		inline GroupNamePtr makeGroupName( const XsString& value ) { return std::make_shared<GroupName>( value ); }
		inline GroupNamePtr makeGroupName( XsString&& value ) { return std::make_shared<GroupName>( std::move( value ) ); }

        class GroupName : public ElementInterface
        {
        public:
            GroupName();
            GroupName( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GroupNameAttributesPtr getAttributes() const;
            void setAttributes( const GroupNameAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            XsString myValue;
            GroupNameAttributesPtr myAttributes;
        };
    }
}
