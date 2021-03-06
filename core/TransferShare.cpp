#include "TransferShare.h"

TransferShare::TransferShare( TransferConstPtr transfer, double share ) : transfer_( transfer ), share_( share ) {
}

int TransferShare::cents() const {
    auto value = floor( transfer_->cents() * share_ );
    return static_cast< int >( value );
}

TransferConstPtr TransferShare::transfer() const {
    return transfer_;
}

double TransferShare::share() const {
    return share_;
}
