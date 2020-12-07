
#ifndef CRUD_W2LSERVICE_HPP
#define CRUD_W2LSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "w2l.hpp"

class W2lService {
public:
  OATPP_COMPONENT(std::shared_ptr<w2l::helper::W2lHelper>, m_w2lHelper); // Inject database component
};

#endif //CRUD_W2LSERVICE_HPP