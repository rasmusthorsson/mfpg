// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( PreBend )

        inline PreBendPtr makePreBend() { return std::make_shared<PreBend>(); }

        class PreBend : public ElementInterface
        {
        public:
            PreBend();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            
            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
