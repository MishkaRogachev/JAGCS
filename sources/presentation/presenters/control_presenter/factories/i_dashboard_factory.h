#ifndef I_DASHBOARD_FACTORY_H
#define I_DASHBOARD_FACTORY_H

namespace presentation
{
    class DashboardPresenter;

    class IDashboardFactory
    {
    public:
        IDashboardFactory() {}
        virtual ~IDashboardFactory() {}

        virtual DashboardPresenter* create() = 0;
    };
}

#endif // I_DASHBOARD_FACTORY_H
